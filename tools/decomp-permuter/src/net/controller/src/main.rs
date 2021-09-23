#![allow(clippy::try_err)]

use std::collections::{HashMap, VecDeque};
use std::convert::TryInto;
use std::default::Default;
use std::io::ErrorKind;
use std::sync::{Arc, Mutex};

use argh::FromArgs;
use serde::{Deserialize, Serialize};
use serde_json::json;
use slotmap::{new_key_type, SlotMap};
use sodiumoxide::crypto::box_;
use sodiumoxide::crypto::sign;
use tokio::fs;
use tokio::io::{AsyncReadExt, AsyncWriteExt};
use tokio::net::tcp::{ReadHalf, WriteHalf};
use tokio::net::{TcpListener, TcpStream};
use tokio::sync::{mpsc, watch, Notify};
use tokio::time;

use crate::db::{ByteString, UserId};
use crate::flimsy_semaphore::FlimsySemaphore;
use crate::port::{ReadPort, WritePort};
use crate::save::SaveableDB;
use crate::util::SimpleResult;

mod client;
mod db;
mod flimsy_semaphore;
mod port;
mod save;
mod server;
mod setup;
mod stats;
mod util;
mod vouch;

const HEARTBEAT_TIME: time::Duration = time::Duration::from_secs(300);

#[derive(FromArgs)]
/// The permuter@home control server.
struct CmdOpts {
    #[argh(subcommand)]
    sub: SubCommand,
}

#[derive(FromArgs)]
#[argh(subcommand)]
enum SubCommand {
    RunServer(RunServerOpts),
    Setup(SetupOpts),
}

#[derive(FromArgs)]
/// Run the permuter@home control server.
#[argh(subcommand, name = "run")]
struct RunServerOpts {
    /// ip:port to listen on (e.g. 0.0.0.0:1234)
    #[argh(option)]
    listen_on: String,

    /// path to TOML configuration file
    #[argh(option)]
    config: String,

    /// path to JSON database
    #[argh(option)]
    db: String,

    /// enable debug logging
    #[argh(switch)]
    debug: bool,
}

#[derive(FromArgs)]
/// Setup initial database and config for permuter@home.
#[argh(subcommand, name = "setup")]
struct SetupOpts {
    /// path to JSON database
    #[argh(option)]
    db: String,
}

#[derive(Deserialize)]
struct Config {
    docker_image: String,
    priv_seed: ByteString<32>,
}

#[derive(Debug, Deserialize, Serialize)]
struct PermuterData {
    fn_name: String,
    #[serde(skip)]
    compressed_source: Vec<u8>,
    #[serde(skip)]
    compressed_target_o_bin: Vec<u8>,
    #[serde(flatten)]
    more_props: HashMap<String, serde_json::Value>,
}

#[derive(Clone, Copy, Debug, Deserialize, Serialize)]
struct PermuterWork {
    seed: u64,
}

#[derive(Debug, Deserialize, Serialize)]
#[serde(tag = "type", rename_all = "snake_case")]
enum ServerUpdate {
    Result {
        #[serde(skip_serializing, default)]
        overhead_us: i64,
        #[serde(skip)]
        compressed_source: Option<Vec<u8>>,
        #[serde(default)]
        has_source: bool,
        #[serde(flatten)]
        more_props: HashMap<String, serde_json::Value>,
    },
    InitDone {
        hash: String,
    },
    InitFailed {
        reason: String,
    },
    Disconnect,
}

#[derive(Debug)]
enum PermuterResult {
    NeedWork,
    Result(UserId, String, ServerUpdate),
}

type PermuterId = u64;

struct Permuter {
    data: Arc<PermuterData>,
    client_id: UserId,
    client_name: String,
    work_queue: VecDeque<PermuterWork>,
    result_tx: mpsc::UnboundedSender<PermuterResult>,
    semaphore: Arc<FlimsySemaphore>,
    priority: f64,
    energy_add: f64,
}

impl Permuter {
    fn send_result(&mut self, res: PermuterResult) {
        // We can't use a blocking semaphore acquire here, because we don't
        // want server sends to block on random client receives. In practice,
        // this is probably fine.
        let _ = self.result_tx.send(res);
        self.semaphore.acquire_ignore_limit();
    }
}

new_key_type! { struct ServerId; }

struct ConnectedServer {
    min_priority: f64,
    num_cores: f64,
}

struct MutableState {
    servers: SlotMap<ServerId, ConnectedServer>,
    permuters: HashMap<PermuterId, Permuter>,
    next_permuter_id: PermuterId,
}

struct State {
    docker_image: String,
    debug: bool,
    sign_sk: sign::SecretKey,
    db: SaveableDB,
    stats_tx: mpsc::Sender<stats::Record>,
    heartbeat_rx: watch::Receiver<()>,
    new_work_notification: Notify,
    m: Mutex<MutableState>,
}

impl State {
    async fn log_stats(&self, record: stats::Record) -> SimpleResult<()> {
        self.stats_tx
            .send(record)
            .await
            .map_err(|_| "stats thread died".into())
    }
}

#[derive(Deserialize)]
#[serde(tag = "method", rename_all = "snake_case")]
enum Request {
    Ping,
    Vouch(vouch::VouchData),
    ConnectServer(server::ConnectServerData),
    ConnectClient(client::ConnectClientData),
}

#[derive(Serialize)]
struct Load {
    clients: usize,
    servers: usize,
    cores: f64,
}

#[tokio::main]
async fn main() -> SimpleResult<()> {
    sodiumoxide::init().map_err(|()| "Failed to initialize cryptography library")?;

    let opts: CmdOpts = argh::from_env();

    match opts.sub {
        SubCommand::RunServer(opts) => run_server(opts).await?,
        SubCommand::Setup(opts) => setup::run_setup(opts)?,
    }
    Ok(())
}

async fn run_server(opts: RunServerOpts) -> SimpleResult<()> {
    let config: Config = toml::from_str(&fs::read_to_string(&opts.config).await?)?;
    let (_, sign_sk) = sign::keypair_from_seed(&config.priv_seed.to_seed());

    let (save_fut, db) = SaveableDB::open(&opts.db)?;
    tokio::spawn(async move {
        if let Err(e) = save_fut.await {
            eprintln!("Failed to save! {:?}", e);
            std::process::exit(1);
        }
    });

    let (stats_fut, stats_tx) = stats::stats_thread(&db);
    tokio::spawn(stats_fut);

    let (heartbeat_tx, heartbeat_rx) = watch::channel(());

    let state: &'static State = Box::leak(Box::new(State {
        docker_image: config.docker_image,
        debug: opts.debug,
        sign_sk,
        db,
        stats_tx,
        heartbeat_rx,
        new_work_notification: Notify::new(),
        m: Mutex::new(MutableState {
            servers: SlotMap::with_key(),
            permuters: HashMap::new(),
            next_permuter_id: 0,
        }),
    }));

    tokio::spawn(async move {
        loop {
            heartbeat_tx.send(()).expect("receiver is still alive");
            time::sleep(HEARTBEAT_TIME).await;
        }
    });

    let listener = TcpListener::bind(opts.listen_on).await?;

    loop {
        let (socket, _) = listener.accept().await?;
        tokio::spawn(async move {
            let mut who = "anonymous".to_string();
            if let Err(e) = handle_connection(socket, state, &mut who).await {
                if let Some(e) = e.downcast_ref::<std::io::Error>() {
                    if matches!(
                        e.kind(),
                        ErrorKind::UnexpectedEof
                            | ErrorKind::ConnectionReset
                            | ErrorKind::TimedOut
                            | ErrorKind::BrokenPipe
                    ) {
                        eprintln!("[{}] disconnected", &who);
                        return;
                    }
                }
                eprintln!("[{}] error: {:?}", &who, e);
            }
        });
    }
}

fn concat<T: Clone>(a: &[T], b: &[T]) -> Vec<T> {
    a.iter().chain(b).cloned().collect()
}

fn concat3<T: Clone>(a: &[T], b: &[T], c: &[T]) -> Vec<T> {
    a.iter().chain(b).chain(c).cloned().collect()
}

async fn handshake<'a>(
    mut rd: ReadHalf<'a>,
    mut wr: WriteHalf<'a>,
    sign_sk: &sign::SecretKey,
) -> SimpleResult<(ReadPort<'a>, WritePort<'a>, UserId, u32)> {
    let mut buffer = [0; 4 + 32];
    rd.read_exact(&mut buffer).await?;
    let (magic, their_pk) = buffer.split_at(4);
    if magic != b"p@h0" {
        Err("Invalid protocol version")?;
    }
    let their_pk = box_::PublicKey::from_slice(&their_pk).unwrap();

    let (our_pk, our_sk) = box_::gen_keypair();
    let signed_data = concat3(b"HELLO:", their_pk.as_ref(), our_pk.as_ref());
    let signature = sign::sign_detached(&signed_data, &sign_sk);
    wr.write_all(&concat(our_pk.as_ref(), signature.as_ref()))
        .await?;

    let key = box_::precompute(&their_pk, &our_sk);
    let mut read_port = ReadPort::new(rd, &key);
    let write_port = WritePort::new(wr, &key);

    let reply = read_port.recv().await?;
    if reply.len() != 32 + 64 + 4 {
        Err("Failed to perform secret handshake")?;
    }
    let (client_ver_key, rest) = reply.split_at(32);
    let (client_signature, permuter_version) = rest.split_at(64);
    let client_ver_key = sign::PublicKey::from_slice(client_ver_key).unwrap();
    let client_signature = sign::Signature::from_slice(client_signature).unwrap();
    let permuter_version = u32::from_be_bytes(permuter_version.try_into().unwrap());
    let signed_data = concat(b"WORLD:", our_pk.as_ref());
    if !sign::verify_detached(&client_signature, &signed_data, &client_ver_key) {
        Err("Spoofed client signature!")?;
    }

    Ok((
        read_port,
        write_port,
        UserId::from_pubkey(&client_ver_key),
        permuter_version,
    ))
}

fn current_load(state: &State, priority: Option<f64>) -> Load {
    let m = state.m.lock().unwrap();
    let mut servers: usize = 0;
    let mut cores: f64 = 0.0;
    for server in m.servers.values() {
        if priority.map_or(true, |p| p >= server.min_priority) {
            servers += 1;
            cores += server.num_cores;
        }
    }
    Load {
        clients: m.permuters.len(),
        servers,
        cores,
    }
}

async fn handle_connection(
    mut socket: TcpStream,
    state: &State,
    out_name: &mut String,
) -> SimpleResult<()> {
    let (rd, wr) = socket.split();
    let (mut read_port, mut write_port, user_id, permuter_version) =
        handshake(rd, wr, &state.sign_sk).await?;
    let name = match state.db.read(|db| {
        let user = db.users.get(&user_id)?;
        Some(user.name.clone())
    }) {
        Some(name) => name,
        None => {
            write_port.send_error("Access denied!").await?;
            Err("Unknown client!")?
        }
    };
    *out_name = name.clone();
    eprintln!("[{}] connected (v {})", &name, permuter_version);
    if state.debug {
        read_port.set_debug(&name);
        write_port.set_debug(&name);
    }
    write_port.send_json(&json!({})).await?;

    let request = read_port.recv().await?;
    let request: Request = serde_json::from_slice(&request)?;
    match request {
        Request::Ping => {
            eprintln!("[{}] ping", &name);
            let load = current_load(state, None);
            write_port.send_json(&load).await?;
        }
        Request::Vouch(data) => {
            vouch::handle_vouch(read_port, write_port, user_id, &name, state, data).await?;
        }
        Request::ConnectServer(data) => {
            server::handle_connect_server(
                read_port,
                write_port,
                user_id,
                &name,
                permuter_version,
                state,
                data,
            )
            .await?;
        }
        Request::ConnectClient(data) => {
            client::handle_connect_client(
                read_port,
                write_port,
                user_id,
                &name,
                permuter_version,
                state,
                data,
            )
            .await?;
        }
    };

    Ok(())
}

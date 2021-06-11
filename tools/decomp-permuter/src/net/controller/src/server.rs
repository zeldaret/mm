use std::collections::{HashMap, HashSet};
use std::sync::{Arc, Mutex};

use serde::{Deserialize, Serialize};
use serde_json::json;
use tokio::sync::{mpsc, mpsc::error::TrySendError, watch, Notify};

use crate::db::UserId;
use crate::port::{ReadPort, WritePort};
use crate::stats;
use crate::util::SimpleResult;
use crate::{
    ConnectedServer, MutableState, PermuterData, PermuterId, PermuterResult, PermuterWork,
    ServerUpdate, State, HEARTBEAT_TIME,
};

const MIN_PERMUTER_VERSION: u32 = 1;

const SERVER_WORK_QUEUE_SIZE: usize = 100;
const TIME_US_GUESS: f64 = 100_000.0;
const MIN_OVERHEAD_US: f64 = 100_000.0;
const MAX_OVERHEAD_FACTOR: i64 = 2;

#[derive(Debug, Deserialize)]
pub(crate) struct ConnectServerData {
    min_priority: f64,
    num_cores: f64,
}

#[derive(Deserialize)]
#[serde(tag = "type", rename_all = "snake_case")]
enum ServerMessage {
    NeedWork,
    Update {
        permuter: PermuterId,
        time_us: f64,
        update: ServerUpdate,
    },
}

enum JobState {
    Loading,
    Loaded,
    Failed,
}

struct Job {
    state: JobState,
    energy: f64,
    active_work: i64,
}

struct ServerState {
    min_priority: f64,
    /// sum of active_work across all jobs
    active_work: i64,
    /// fractional part of how much work should be requested, in [0, 1)
    more_work_acc: f64,
    jobs: HashMap<PermuterId, Job>,
}

async fn server_read(
    port: &mut ReadPort<'_>,
    who_id: &UserId,
    who_name: &str,
    server_state: &Mutex<ServerState>,
    state: &State,
    more_work_tx: mpsc::Sender<()>,
    new_permuter: &Notify,
) -> SimpleResult<()> {
    loop {
        let msg = port.recv().await?;
        let mut msg: ServerMessage = serde_json::from_slice(&msg)?;
        if let ServerMessage::Update {
            update:
                ServerUpdate::Result {
                    ref mut compressed_source,
                    has_source: true,
                    ..
                },
            ..
        } = msg
        {
            *compressed_source = Some(port.recv().await?);
        }

        let mut has_new = false;
        let mut request_work;

        {
            let mut m = state.m.lock().unwrap();
            let mut server_state = server_state.lock().unwrap();

            let mut more_work: f64 = 1.0;

            if let ServerMessage::Update {
                permuter: perm_id,
                update,
                time_us,
            } = msg
            {
                // If we get back a message referring to a since-removed
                // permuter, no need to do anything. Just request one more
                // piece of work to make up for it.
                if let Some(job) = server_state.jobs.get_mut(&perm_id) {
                    if let Some(perm) = m.permuters.get_mut(&perm_id) {
                        job.energy += perm.energy_add * time_us;

                        match update {
                            ServerUpdate::InitDone { .. } => {
                                if !matches!(job.state, JobState::Loading) {
                                    Err("Got InitDone while not in Loading state")?;
                                }
                                job.state = JobState::Loaded;
                                has_new = true;
                            }
                            ServerUpdate::InitFailed { .. } => {
                                if !matches!(job.state, JobState::Loading) {
                                    Err("Got InitFailed while not in Loading state")?;
                                }
                                job.state = JobState::Failed;
                            }
                            ServerUpdate::Disconnect { .. } => {
                                if !matches!(job.state, JobState::Loaded) {
                                    Err("Got Disconnect while not in Loaded state")?;
                                }
                                job.state = JobState::Failed;
                                let work = job.active_work;
                                job.active_work = 0;
                                server_state.active_work -= work;
                                more_work = 0.0;
                            }
                            ServerUpdate::Result { overhead_us, .. } => {
                                if !matches!(job.state, JobState::Loaded) {
                                    Err("Got result while not in Loaded state")?;
                                }
                                // If the work item spent less than some given
                                // amount of time in queues, request more work.
                                // This ensures we saturate all server cores.
                                // On the other hand, if it spends too much time
                                // in queues, it's best if we reduce the amount
                                // of work.
                                // We don't need to adjust for time spent on the
                                // network, because we have backpressure on slow
                                // writes on both ends, and read continuously.
                                job.active_work -= 1;
                                server_state.active_work -= 1;
                                let min_overhead_us = (time_us + MIN_OVERHEAD_US) as i64;
                                if overhead_us == 0 {
                                    // Legacy server, skip this logic.
                                } else if overhead_us > MAX_OVERHEAD_FACTOR * min_overhead_us {
                                    more_work = 0.5;
                                } else if overhead_us < min_overhead_us {
                                    more_work = 1.5;
                                }
                            }
                        }
                        perm.send_result(PermuterResult::Result(
                            who_id.clone(),
                            who_name.to_string(),
                            update,
                        ));
                    }
                }
            }

            more_work += server_state.more_work_acc;
            request_work = more_work as i32;
            server_state.more_work_acc = more_work - request_work as f64;

            if request_work == 0
                && server_state.active_work == 0
                && more_work_tx.capacity() == SERVER_WORK_QUEUE_SIZE
            {
                // Don't request 0 work if it would lead to total starvation.
                request_work = 1;
            }
        }

        if has_new {
            new_permuter.notify_waiters();
            state
                .log_stats(stats::Record::ServerNewFunction {
                    server: who_id.clone(),
                })
                .await?;
        }

        for _ in 0..request_work {
            // Try requesting more work by sending a message to the writer thread.
            // If the queue is full (because the writer thread is blocked on a
            // send), drop the request to avoid an unbounded backlog.
            if let Err(TrySendError::Closed(_)) = more_work_tx.try_send(()) {
                panic!("work chooser must not close except on error");
            }
        }
    }
}

#[derive(Serialize)]
#[serde(tag = "type", rename_all = "snake_case")]
enum ToSend {
    Work(PermuterWork),
    Add {
        client_id: UserId,
        client_name: String,
        data: Arc<PermuterData>,
    },
    Remove,
}

#[derive(Serialize)]
struct OutMessage {
    permuter: PermuterId,
    #[serde(flatten)]
    to_send: ToSend,
}

fn try_next_work_message(
    m: &mut MutableState,
    server_state: &mut ServerState,
) -> Option<OutMessage> {
    let mut skip = HashSet::new();
    loop {
        // If possible, send a new permuter.
        if let Some((&perm_id, perm)) = m
            .permuters
            .iter()
            .find(|(&perm_id, _)| !server_state.jobs.contains_key(&perm_id))
        {
            server_state.jobs.insert(
                perm_id,
                Job {
                    state: JobState::Loading,
                    energy: 0.0,
                    active_work: 0,
                },
            );
            return Some(OutMessage {
                permuter: perm_id,
                to_send: ToSend::Add {
                    client_id: perm.client_id.clone(),
                    client_name: perm.client_name.clone(),
                    data: perm.data.clone(),
                },
            });
        }

        // If none, find an existing one to work on, or to remove.
        let mut best_cost = 0.0;
        let mut best: Option<(PermuterId, &mut Job)> = None;
        let min_priority = server_state.min_priority;
        for (&perm_id, job) in server_state.jobs.iter_mut() {
            if let Some(perm) = m.permuters.get(&perm_id) {
                let energy =
                    job.energy + (job.active_work as f64) * perm.energy_add * TIME_US_GUESS;
                if matches!(job.state, JobState::Loaded)
                    && !skip.contains(&perm_id)
                    && perm.priority >= min_priority
                    && (best.is_none() || energy < best_cost)
                {
                    best_cost = energy;
                    best = Some((perm_id, job));
                }
            } else {
                server_state.active_work -= job.active_work;
                server_state.jobs.remove(&perm_id);
                return Some(OutMessage {
                    permuter: perm_id,
                    to_send: ToSend::Remove,
                });
            }
        }

        let (perm_id, job) = match best {
            None => return None,
            Some(tup) => tup,
        };

        let perm = m.permuters.get_mut(&perm_id).unwrap();
        let work = match perm.work_queue.pop_front() {
            None => {
                // Chosen permuter is out of work. Ask it for more, and try
                // again without it as a candidate. When the queue becomes
                // non-empty again all sleeping writers will be notified.
                perm.send_result(PermuterResult::NeedWork);
                skip.insert(perm_id);
                continue;
            }
            Some(work) => work,
        };

        perm.semaphore.release();

        let min_energy = job.energy;
        job.active_work += 1;
        server_state.active_work += 1;

        // Adjust energies to be around zero, to avoid problems with float
        // imprecision, and to ensure that new permuters that come in with
        // energy zero will fit the schedule.
        for job in server_state.jobs.values_mut() {
            job.energy -= min_energy;
        }

        return Some(OutMessage {
            permuter: perm_id,
            to_send: ToSend::Work(work),
        });
    }
}

async fn next_work_message(
    server_state: &Mutex<ServerState>,
    state: &State,
    new_permuter: &Notify,
) -> OutMessage {
    let mut wait_for = None;
    loop {
        if let Some(waiter) = wait_for {
            waiter.await;
        }
        let mut m = state.m.lock().unwrap();
        let mut server_state = server_state.lock().unwrap();
        match try_next_work_message(&mut m, &mut server_state) {
            Some(message) => return message,
            None => {
                // Nothing to work on! Register to be notified when something
                // happens (while the lock is still held) and go to sleep.
                let n1 = state.new_work_notification.notified();
                let n2 = new_permuter.notified();
                wait_for = Some(async move {
                    tokio::select! {
                        () = n1 => {}
                        () = n2 => {}
                    }
                });
            }
        }
    }
}

fn requires_response(work: &OutMessage) -> bool {
    match work.to_send {
        ToSend::Work { .. } => true,
        ToSend::Add { .. } => true,
        ToSend::Remove => false,
    }
}

async fn server_choose_work(
    server_state: &Mutex<ServerState>,
    state: &State,
    mut more_work_rx: mpsc::Receiver<()>,
    next_message_tx: mpsc::Sender<OutMessage>,
    wrote_message: &Notify,
    new_permuter: &Notify,
) -> SimpleResult<()> {
    loop {
        let message = next_work_message(server_state, state, new_permuter).await;
        let requires_response = requires_response(&message);
        next_message_tx
            .send(message)
            .await
            .map_err(|_| ())
            .expect("writer must not close except on error");
        wrote_message.notified().await;
        if requires_response {
            more_work_rx
                .recv()
                .await
                .expect("reader must not close except on error");
        }
    }
}

async fn send_heartbeat(port: &mut WritePort<'_>) -> SimpleResult<()> {
    port.send_json(&json!({
        "type": "heartbeat",
    }))
    .await
}

async fn send_work(port: &mut WritePort<'_>, work: &OutMessage) -> SimpleResult<()> {
    port.send_json(&work).await?;
    if let ToSend::Add { ref data, .. } = work.to_send {
        port.send(&data.compressed_source).await?;
        port.send(&data.compressed_target_o_bin).await?;
    }
    Ok(())
}

async fn server_write(
    port: &mut WritePort<'_>,
    mut next_message_rx: mpsc::Receiver<OutMessage>,
    mut heartbeat_rx: watch::Receiver<()>,
    wrote_message: &Notify,
) -> SimpleResult<()> {
    loop {
        tokio::select! {
            work = next_message_rx.recv() => {
                let work = work.expect("chooser must not close except on error");
                send_work(port, &work).await?;
                wrote_message.notify_one();
            }
            res = heartbeat_rx.changed() => {
                res.expect("heartbeat thread panicked");
                send_heartbeat(port).await?;
            }
        }
    }
}

pub(crate) async fn handle_connect_server<'a>(
    mut read_port: ReadPort<'a>,
    mut write_port: WritePort<'a>,
    who_id: UserId,
    who_name: &str,
    permuter_version: u32,
    state: &State,
    data: ConnectServerData,
) -> SimpleResult<()> {
    if permuter_version < MIN_PERMUTER_VERSION {
        Err("Permuter version too old!")?;
    }

    eprintln!(
        "[{}] start server ({}, {})",
        who_name, data.min_priority, data.num_cores
    );

    write_port
        .send_json(&json!({
            "docker_image": &state.docker_image,
            "heartbeat_interval": HEARTBEAT_TIME.as_secs(),
        }))
        .await?;

    let (more_work_tx, more_work_rx) = mpsc::channel(SERVER_WORK_QUEUE_SIZE);
    let (next_message_tx, next_message_rx) = mpsc::channel(1);
    let wrote_message = Notify::new();
    let new_permuter = Notify::new();

    let mut server_state = Mutex::new(ServerState {
        min_priority: data.min_priority,
        active_work: 0,
        more_work_acc: 0.0,
        jobs: HashMap::new(),
    });

    let id = state.m.lock().unwrap().servers.insert(ConnectedServer {
        min_priority: data.min_priority,
        num_cores: data.num_cores,
    });

    let r = tokio::try_join!(
        server_read(
            &mut read_port,
            &who_id,
            who_name,
            &server_state,
            state,
            more_work_tx,
            &new_permuter,
        ),
        server_choose_work(
            &server_state,
            state,
            more_work_rx,
            next_message_tx,
            &wrote_message,
            &new_permuter,
        ),
        server_write(
            &mut write_port,
            next_message_rx,
            state.heartbeat_rx.clone(),
            &wrote_message,
        )
    );

    {
        let mut m = state.m.lock().unwrap();
        for (&perm_id, job) in &server_state.get_mut().unwrap().jobs {
            if let JobState::Loaded = job.state {
                if let Some(perm) = m.permuters.get_mut(&perm_id) {
                    perm.send_result(PermuterResult::Result(
                        who_id.clone(),
                        who_name.to_string(),
                        ServerUpdate::Disconnect,
                    ));
                }
            }
        }

        m.servers.remove(id);
    }
    r?;
    Ok(())
}

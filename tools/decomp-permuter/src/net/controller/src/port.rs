use std::convert::TryInto;

use chrono::Local;
use serde::Serialize;
use sodiumoxide::crypto::box_;
use sodiumoxide::crypto::box_::{Nonce, PrecomputedKey};
use tokio::io::{AsyncReadExt, AsyncWriteExt};
use tokio::net::tcp::{ReadHalf, WriteHalf};

use crate::util::SimpleResult;

fn debug_print(action: &str, who: &str, msg: &[u8]) {
    let time = Local::now().format("%H:%M:%S:%f");
    if msg.len() <= 300 {
        let msg = String::from_utf8(
            msg.iter()
                .copied()
                .flat_map(std::ascii::escape_default)
                .collect(),
        )
        .unwrap();
        println!("{} debug: {} {}: {}", time, action, who, msg);
    } else {
        println!("{} debug: {} {}: {} bytes", time, action, who, msg.len());
    }
}

pub struct ReadPort<'a> {
    read_half: ReadHalf<'a>,
    key: PrecomputedKey,
    nonce: u64,
    debug_name: Option<&'a str>,
}

impl<'a> ReadPort<'a> {
    pub fn new(read_half: ReadHalf<'a>, key: &PrecomputedKey) -> Self {
        ReadPort {
            read_half,
            key: key.clone(),
            nonce: 0,
            debug_name: None,
        }
    }

    pub fn set_debug(&mut self, name: &'a str) {
        self.debug_name = Some(name);
    }

    pub async fn recv(&mut self) -> SimpleResult<Vec<u8>> {
        let len = self.read_half.read_u64().await?;
        if len >= (1 << 48) {
            Err("Unreasonable packet length")?
        }
        let mut buffer = vec![0; len.try_into()?];
        self.read_half.read_exact(&mut buffer).await?;
        let nonce = nonce_from_u64(self.nonce);
        self.nonce += 2;
        let data =
            box_::open_precomputed(&buffer, &nonce, &self.key).map_err(|()| "Failed to decrypt")?;
        if let Some(name) = self.debug_name {
            debug_print("Receive from", name, &data);
        }
        Ok(data)
    }
}

pub struct WritePort<'a> {
    write_half: WriteHalf<'a>,
    key: PrecomputedKey,
    nonce: u64,
    debug_name: Option<&'a str>,
}

impl<'a> WritePort<'a> {
    pub fn new(write_half: WriteHalf<'a>, key: &PrecomputedKey) -> Self {
        WritePort {
            write_half,
            key: key.clone(),
            nonce: 1,
            debug_name: None,
        }
    }

    pub fn set_debug(&mut self, name: &'a str) {
        self.debug_name = Some(name);
    }

    pub async fn send(&mut self, data: &[u8]) -> SimpleResult<()> {
        if let Some(name) = self.debug_name {
            debug_print("Send to", name, &data);
        }
        let nonce = nonce_from_u64(self.nonce);
        self.nonce += 2;
        let data = box_::seal_precomputed(data, &nonce, &self.key);
        self.write_half.write_u64(data.len() as u64).await?;
        self.write_half.write_all(&data).await?;
        Ok(())
    }

    pub async fn send_json<T: ?Sized>(&mut self, value: &T) -> SimpleResult<()>
    where
        T: Serialize,
    {
        self.send(&serde_json::to_vec(value)?).await
    }

    pub async fn send_error(&mut self, message: &str) -> SimpleResult<()> {
        self.send_json(message).await
    }
}

fn nonce_from_u64(num: u64) -> Nonce {
    let nonce_bytes = [[0; 8], [0; 8], num.to_be_bytes()].concat();
    Nonce::from_slice(&nonce_bytes).unwrap()
}

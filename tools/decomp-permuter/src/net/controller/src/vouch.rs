use std::str;

use hex::FromHex;
use serde::Deserialize;
use serde_json::json;
use sodiumoxide::crypto::sign;

use crate::db::{User, UserId};
use crate::port::{ReadPort, WritePort};
use crate::util::SimpleResult;
use crate::{concat, State};

#[derive(Debug, Deserialize)]
pub(crate) struct VouchData {
    who: UserId,
    signed_name: String,
}

fn verify_with_magic<'a>(
    magic: &[u8],
    data: &'a [u8],
    key: &sign::PublicKey,
) -> SimpleResult<&'a [u8]> {
    if data.len() < 64 {
        Err("signature too short")?;
    }
    let (signature, data) = data.split_at(64);
    let signed_data = concat(magic, data);
    let signature = sign::Signature::from_slice(signature).unwrap();
    if !sign::verify_detached(&signature, &signed_data, key) {
        Err("bad signature")?;
    }
    Ok(data)
}

fn parse_signed_name(signed_name: &str, who: &UserId) -> SimpleResult<String> {
    let signed_name = Vec::from_hex(signed_name).map_err(|_| "not a valid hex string")?;
    let name_bytes = verify_with_magic(b"NAME:", &signed_name, &who.to_pubkey())?;
    let name = str::from_utf8(name_bytes)?;
    if name.is_empty() {
        Err("name is empty")?;
    }
    if name.chars().any(char::is_control) {
        Err("name cannot contain control characters")?;
    }
    Ok(name.to_string())
}

pub(crate) async fn handle_vouch<'a>(
    mut read_port: ReadPort<'a>,
    mut write_port: WritePort<'a>,
    who_id: UserId,
    who_name: &str,
    state: &State,
    data: VouchData,
) -> SimpleResult<()> {
    let vouchee_name = match parse_signed_name(&data.signed_name, &data.who) {
        Ok(name) => name,
        Err(e) => {
            write_port.send_error(&format!("{}", &e)).await?;
            Err(e)?
        }
    };
    write_port.send_json(&json!({})).await?;
    read_port.recv().await?;
    state
        .db
        .write(true, |db| {
            db.users.entry(data.who).or_insert_with(|| User {
                trusted_by: Some(who_id),
                name: vouchee_name.clone(),
                client_stats: Default::default(),
                server_stats: Default::default(),
            });
        })
        .await;
    write_port.send_json(&json!({})).await?;
    eprintln!("[{}] vouch {}", who_name, &vouchee_name);
    Ok(())
}

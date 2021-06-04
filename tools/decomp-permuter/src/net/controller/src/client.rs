use std::collections::VecDeque;
use std::sync::Arc;

use serde::{Deserialize, Serialize};
use serde_json::json;
use tokio::sync::mpsc;

use crate::db::UserId;
use crate::flimsy_semaphore::FlimsySemaphore;
use crate::port::{ReadPort, WritePort};
use crate::stats;
use crate::util::SimpleResult;
use crate::{
    current_load, Permuter, PermuterData, PermuterId, PermuterResult, PermuterWork, ServerUpdate,
    State,
};

const MIN_PERMUTER_VERSION: u32 = 1;

const CLIENT_MAX_QUEUES_SIZE: usize = 100;
const MIN_PRIORITY: f64 = 0.001;
const MAX_PRIORITY: f64 = 10.0;

#[derive(Debug, Deserialize)]
pub(crate) struct ConnectClientData {
    priority: f64,
}

#[derive(Deserialize)]
#[serde(tag = "type", rename_all = "snake_case")]
enum ClientMessage {
    Work { work: PermuterWork },
}

#[derive(Serialize)]
struct PermuterResultMessage<'a> {
    server: String,
    #[serde(flatten)]
    update: &'a ServerUpdate,
}

async fn client_read(
    port: &mut ReadPort<'_>,
    perm_id: &PermuterId,
    semaphore: &FlimsySemaphore,
    state: &State,
) -> SimpleResult<()> {
    loop {
        let msg = port.recv().await?;
        let msg: ClientMessage = serde_json::from_slice(&msg)?;
        let ClientMessage::Work { work } = msg;

        // Avoid the work and result queues growing indefinitely by restricting
        // their combined size with a semaphore.
        semaphore.acquire().await;

        let mut m = state.m.lock().unwrap();
        let perm = m.permuters.get_mut(perm_id).unwrap();
        if perm.work_queue.is_empty() {
            state.new_work_notification.notify_waiters();
        }
        perm.work_queue.push_back(work);
    }
}

async fn client_write(
    port: &mut WritePort<'_>,
    fn_name: &str,
    semaphore: &FlimsySemaphore,
    state: &State,
    mut result_rx: mpsc::UnboundedReceiver<PermuterResult>,
    client_id: &UserId,
) -> SimpleResult<()> {
    loop {
        let res = result_rx.recv().await.unwrap();
        semaphore.release();

        match res {
            PermuterResult::NeedWork => {
                port.send_json(&json!({
                    "type": "need_work",
                }))
                .await?;
            }
            PermuterResult::Result(server_id, server_name, server_update) => {
                port.send_json(&PermuterResultMessage {
                    server: server_name,
                    update: &server_update,
                })
                .await?;

                if let ServerUpdate::Result {
                    compressed_source,
                    ref more_props,
                    ..
                } = server_update
                {
                    if let Some(ref data) = compressed_source {
                        port.send(data).await?;
                    }

                    let score = more_props.get("score").and_then(|score| score.as_i64());
                    let outcome = if compressed_source.is_none() {
                        stats::Outcome::Unhelpful
                    } else if matches!(score, Some(0)) {
                        stats::Outcome::Matched
                    } else {
                        stats::Outcome::Improved
                    };
                    state
                        .log_stats(stats::Record::WorkDone {
                            server: server_id,
                            client: client_id.clone(),
                            fn_name: fn_name.to_string(),
                            outcome,
                        })
                        .await?;
                }
            }
        }
    }
}

pub(crate) async fn handle_connect_client<'a>(
    mut read_port: ReadPort<'a>,
    mut write_port: WritePort<'a>,
    who_id: UserId,
    who_name: &str,
    permuter_version: u32,
    state: &State,
    data: ConnectClientData,
) -> SimpleResult<()> {
    if permuter_version < MIN_PERMUTER_VERSION {
        Err("Permuter version too old!")?;
    }

    if !(MIN_PRIORITY <= data.priority && data.priority <= MAX_PRIORITY) {
        Err("Priority out of range")?;
    }

    let load = current_load(state, Some(data.priority));
    write_port.send_json(&load).await?;

    let permuter_data = read_port.recv().await?;
    let mut permuter_data: PermuterData = serde_json::from_slice(&permuter_data)?;
    permuter_data.compressed_source = read_port.recv().await?;
    permuter_data.compressed_target_o_bin = read_port.recv().await?;
    write_port.send_json(&json!({})).await?;

    eprintln!(
        "[{}] start client ({}, {})",
        &who_name, &permuter_data.fn_name, data.priority
    );

    state
        .log_stats(stats::Record::ClientNewFunction {
            client: who_id.clone(),
            fn_name: permuter_data.fn_name.clone(),
        })
        .await?;

    let energy_add = 1.0 / data.priority;
    let fn_name = permuter_data.fn_name.clone();

    let (result_tx, result_rx) = mpsc::unbounded_channel();
    let semaphore = Arc::new(FlimsySemaphore::new(CLIENT_MAX_QUEUES_SIZE));

    let perm_id = {
        let mut m = state.m.lock().unwrap();
        let id = m.next_permuter_id;
        m.next_permuter_id += 1;
        m.permuters.insert(
            id,
            Permuter {
                data: permuter_data.into(),
                client_id: who_id.clone(),
                client_name: who_name.to_string(),
                work_queue: VecDeque::new(),
                result_tx: result_tx.clone(),
                semaphore: semaphore.clone(),
                priority: data.priority,
                energy_add,
            },
        );
        state.new_work_notification.notify_waiters();
        id
    };

    let r = tokio::try_join!(
        client_read(&mut read_port, &perm_id, &semaphore, state),
        client_write(
            &mut write_port,
            &fn_name,
            &semaphore,
            state,
            result_rx,
            &who_id
        )
    );

    state.m.lock().unwrap().permuters.remove(&perm_id);
    state.new_work_notification.notify_waiters();
    r?;
    Ok(())
}

use std::future::Future;

use tokio::sync::mpsc;

use crate::db::{Stats, UserId};
use crate::save::SaveableDB;

const CHANNEL_CAPACITY: usize = 10000;

#[derive(Clone, Copy)]
pub enum Outcome {
    Matched,
    Improved,
    Unhelpful,
}

pub enum Record {
    WorkDone {
        server: UserId,
        client: UserId,
        fn_name: String,
        outcome: Outcome,
    },
    ClientNewFunction {
        client: UserId,
        fn_name: String,
    },
    ServerNewFunction {
        server: UserId,
    },
}

fn add_stats(stats: &mut Stats, outcome: Outcome) {
    if matches!(outcome, Outcome::Matched) {
        stats.matches += 1;
    }
    if matches!(outcome, Outcome::Matched | Outcome::Improved) {
        stats.improvements += 1;
    }
    stats.iterations += 1;
}

async fn stats_writer(db: &SaveableDB, mut rx: mpsc::Receiver<Record>) {
    loop {
        let record = rx.recv().await.unwrap();
        db.write(false, |db| {
            match record {
                Record::WorkDone {
                    server,
                    client,
                    fn_name,
                    outcome,
                } => {
                    add_stats(&mut db.total_stats, outcome);
                    add_stats(db.func_stat(fn_name), outcome);
                    if let Some(user) = db.users.get_mut(&client) {
                        add_stats(&mut user.client_stats, outcome);
                    }
                    if let Some(user) = db.users.get_mut(&server) {
                        add_stats(&mut user.server_stats, outcome);
                    }
                }
                Record::ClientNewFunction { client, fn_name } => {
                    db.func_stat(fn_name).functions += 1;
                    if let Some(user) = db.users.get_mut(&client) {
                        user.client_stats.functions += 1;
                    }
                    db.total_stats.functions += 1;
                }
                Record::ServerNewFunction { server } => {
                    if let Some(user) = db.users.get_mut(&server) {
                        user.server_stats.functions += 1;
                    }
                }
            };
        })
        .await;
    }
}

pub fn stats_thread(db: &SaveableDB) -> (impl Future<Output = ()>, mpsc::Sender<Record>) {
    let (tx, rx) = mpsc::channel(CHANNEL_CAPACITY);
    let db = db.clone();
    let fut = async move {
        stats_writer(&db, rx).await;
    };
    (fut, tx)
}

use std::future::Future;
use std::io::Write;
use std::path::{Path, PathBuf};
use std::sync::{Arc, RwLock};
use std::time::Duration;

use tempfile::NamedTempFile;
use tokio::sync::{mpsc, oneshot};
use tokio::time::timeout;

use crate::db::DB;
use crate::util::{FutureExt, SimpleResult};

const SAVE_INTERVAL: Duration = Duration::from_secs(30);

enum SaveType {
    Delayed,
    Immediate(oneshot::Sender<()>),
}

struct InnerSaveableDB {
    db: DB,
    stale: bool,
    save_chan: mpsc::UnboundedSender<SaveType>,
}

#[derive(Clone)]
pub struct SaveableDB(Arc<RwLock<InnerSaveableDB>>);

async fn save_db_loop(
    db: SaveableDB,
    path: &Path,
    mut save_channel: mpsc::UnboundedReceiver<SaveType>,
) -> SimpleResult<()> {
    loop {
        let mut done_chans = Vec::new();
        match save_channel.recv().await {
            None => return Ok(()),
            Some(SaveType::Immediate(chan)) => {
                done_chans.push(chan);
            }
            Some(SaveType::Delayed) => {
                // Wait for SAVE_INTERVAL or until we receive an Immediate save.
                let _ = timeout(SAVE_INTERVAL, async {
                    loop {
                        match save_channel.recv().await {
                            None => {
                                break;
                            }
                            Some(SaveType::Immediate(chan)) => {
                                done_chans.push(chan);
                                break;
                            }
                            Some(SaveType::Delayed) => {}
                        };
                    }
                })
                .await;
            }
        };

        // Clear the queue in case more messages have stacked up past an
        // Immediate. Receiver::try_recv() is temporarily dead as of tokio 1.4
        // (https://github.com/tokio-rs/tokio/issues/3350) due to a bug where
        // messages can be delayed, but in this case that doesn't matter.
        loop {
            match save_channel.recv().now_or_never().await {
                None | Some(None) => {
                    break;
                }
                Some(Some(SaveType::Immediate(chan))) => {
                    done_chans.push(chan);
                }
                Some(Some(SaveType::Delayed)) => {}
            };
        }

        // Mark the DB as non-stale, to start receiving save messages again.
        db.0.write().unwrap().stale = false;

        // Actually do the save, by first serializing, then atomically saving
        // the file by creating and renaming a temp file in the same directory.
        let data = db.read(|db| serde_json::to_string(&db).unwrap());

        let r: SimpleResult<()> = tokio::task::block_in_place(|| {
            let parent_dir = path.parent().unwrap_or_else(|| Path::new("."));
            let mut tempf = NamedTempFile::new_in(parent_dir)?;
            tempf.write_all(data.as_bytes())?;
            tempf.as_file().sync_all()?;
            tempf.persist(path)?;
            Ok(())
        });
        r?;

        for chan in done_chans {
            let _ = chan.send(());
        }
    }
}

impl SaveableDB {
    pub fn open(
        filename: &str,
    ) -> SimpleResult<(impl Future<Output = SimpleResult<()>>, SaveableDB)> {
        let db_file = std::fs::File::open(filename)?;
        let db: DB = serde_json::from_reader(&db_file)?;

        let (save_tx, save_rx) = mpsc::unbounded_channel();

        let saveable_db = SaveableDB(Arc::new(RwLock::new(InnerSaveableDB {
            db,
            stale: false,
            save_chan: save_tx,
        })));

        let path = PathBuf::from(filename);
        let db2 = saveable_db.clone();

        let fut = async move { save_db_loop(db2, &path, save_rx).await };
        Ok((fut, saveable_db))
    }

    pub fn read<T>(&self, callback: impl FnOnce(&DB) -> T) -> T {
        let inner = self.0.read().unwrap();
        callback(&inner.db)
    }

    pub async fn write<T>(&self, immediate: bool, callback: impl FnOnce(&mut DB) -> T) -> T {
        let ret;
        let rx2;
        {
            let mut inner = self.0.write().unwrap();
            ret = callback(&mut inner.db);
            if immediate {
                inner.stale = true;
                let (tx, rx) = oneshot::channel();
                rx2 = rx;
                inner
                    .save_chan
                    .send(SaveType::Immediate(tx))
                    .map_err(|_| ())
                    .expect("Failed to send message to save task");
            } else {
                if !inner.stale {
                    inner.stale = true;
                    inner
                        .save_chan
                        .send(SaveType::Delayed)
                        .map_err(|_| ())
                        .expect("Failed to send message to save task");
                }
                return ret;
            }
        }
        rx2.await.expect("Failed to save!");
        ret
    }
}

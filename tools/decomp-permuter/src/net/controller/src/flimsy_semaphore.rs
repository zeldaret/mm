use std::convert::TryInto;
use std::sync::atomic::{AtomicIsize, Ordering};

use tokio::sync::Notify;

/// An unfair semaphore that allows overdrafts.
pub struct FlimsySemaphore {
    notify: Notify,
    slots: AtomicIsize,
}

impl FlimsySemaphore {
    // Invariant: if `slots` has ever become non-positive, then if positive
    // there will be a notify token in circulation. Taking the token
    // synchronizes with a positive `slots`.
    pub fn new(limit: usize) -> FlimsySemaphore {
        FlimsySemaphore {
            notify: Notify::new(),
            slots: AtomicIsize::new(limit.try_into().unwrap()),
        }
    }

    pub fn acquire_ignore_limit(&self) {
        self.slots.fetch_add(-1, Ordering::Acquire);
    }

    pub async fn acquire(&self) {
        let mut was_woken = false;
        let mut val = self.slots.load(Ordering::Relaxed);
        loop {
            if val > 0 {
                match self.slots.compare_exchange(
                    val,
                    val - 1,
                    Ordering::Acquire,
                    Ordering::Relaxed,
                ) {
                    Ok(_) => {
                        if was_woken && val > 1 {
                            self.notify.notify_one();
                        }
                        return;
                    }
                    Err(actually) => {
                        val = actually;
                    }
                }
            } else {
                self.notify.notified().await;
                was_woken = true;
                val = self.slots.load(Ordering::Relaxed);
            }
        }
    }

    pub fn release(&self) {
        if self.slots.fetch_add(1, Ordering::Release) == 0 {
            self.notify.notify_one();
        }
    }
}

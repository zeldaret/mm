use std::error::Error;
use std::future::Future;
use std::pin::Pin;
use std::task::{Context, Poll};

use pin_project::pin_project;

pub type SimpleResult<T> = Result<T, Box<dyn Error + Send + Sync>>;

#[pin_project]
pub struct NowOrNever<F: Future> {
    #[pin]
    inner: F,
}

impl<F: Future> Future for NowOrNever<F> {
    type Output = Option<F::Output>;

    fn poll(self: Pin<&mut Self>, cx: &mut Context<'_>) -> Poll<Self::Output> {
        let ret = self.project().inner.poll(cx);
        Poll::Ready(match ret {
            Poll::Pending => None,
            Poll::Ready(val) => Some(val),
        })
    }
}

impl<T> FutureExt for T where T: Future {}

pub trait FutureExt: Future {
    fn now_or_never(self) -> NowOrNever<Self>
    where
        Self: Sized,
    {
        NowOrNever { inner: self }
    }
}

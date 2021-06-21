#include <ultra64.h>
#include <global.h>

void osStartThread(OSThread* t) {
    register u32 saveMask;

    saveMask = __osDisableInt();

    switch (t->state) {
        case 8:
            t->state = 2;
            __osEnqueueThread(&__osRunQueue, t);
            break;
        case 1:
            if ((t->queue == NULL) || (t->queue == &__osRunQueue)) {
                t->state = 2;
                __osEnqueueThread(&__osRunQueue, t);
            } else {
                t->state = 8;
                __osEnqueueThread(t->queue, t);
                __osEnqueueThread(&__osRunQueue, __osPopThread(t->queue));
            }
            break;
    }

    if (__osRunningThread == NULL) {
        __osDispatchThread();
    } else {
        if (__osRunningThread->priority < __osRunQueue->priority) {
            __osRunningThread->state = 2;
            __osEnqueueAndYield(&__osRunQueue);
        }
    }

    __osRestoreInt(saveMask);
}

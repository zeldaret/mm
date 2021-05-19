#include <ultra64.h>
#include <global.h>

void osStopThread(OSThread* t) {
    register u32 saveMask;
    register u16 state;

    saveMask = __osDisableInt();

    if (t == NULL) {
        state = 4;
    } else {
        state = t->state;
    }

    switch (state) {
        case 4:
            __osRunningThread->state = 1;
            __osEnqueueAndYield(NULL);
            break;
        case 2:
        case 8:
            t->state = 1;
            __osDequeueThread(t->queue, t);
            break;
    }

    __osRestoreInt(saveMask);
}

#include "global.h"

void osYieldThread(void) {
    register u32 saveMask = __osDisableInt();

    __osRunningThread->state = 2;
    __osEnqueueAndYield(&__osRunQueue);

    __osRestoreInt(saveMask);
}

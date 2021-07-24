#include "ultra64.h"
#include "global.h"

OSTime osGetTime(void) {
    u32 CurrentCount;
    u32 elapseCount;
    OSTime sp28;
    register u32 savedMask;

    savedMask = __osDisableInt();

    CurrentCount = osGetCount();
    elapseCount = CurrentCount - __osBaseCounter;
    sp28 = __osCurrentTime;

    __osRestoreInt(savedMask);

    return elapseCount + sp28;
}

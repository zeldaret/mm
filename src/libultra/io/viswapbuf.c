#include "ultra64.h"
#include "global.h"

void osViSwapBuffer(void* frameBufPtr) {

    u32 saveMask = __osDisableInt();

    __osViNext->framep = frameBufPtr;
    __osViNext->state |= 0x10;

    __osRestoreInt(saveMask);
}

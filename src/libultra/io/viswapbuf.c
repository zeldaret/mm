#include "global.h"

void osViSwapBuffer(void* frameBufPtr) {

    u32 saveMask = __osDisableInt();

    __osViNext->buffer = frameBufPtr;
    __osViNext->state |= 0x10;

    __osRestoreInt(saveMask);
}

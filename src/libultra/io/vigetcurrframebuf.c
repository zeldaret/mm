#include "global.h"

u32* osViGetCurrentFramebuffer(void) {
    register u32 prevInt = __osDisableInt();
    u32* curBuf = __osViCurr->buffer;

    __osRestoreInt(prevInt);

    return curBuf;
}

#include "global.h"

void* osViGetNextFramebuffer(void) {
    register u32 saveMask;
    void* buffer;

    saveMask = __osDisableInt();

    buffer = __osViNext->buffer;

    __osRestoreInt(saveMask);

    return buffer;
}

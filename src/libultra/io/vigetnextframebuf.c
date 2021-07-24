#include "ultra64.h"
#include "global.h"

void* osViGetNextFramebuffer(void) {
    register u32 saveMask;
    void* framep;

    saveMask = __osDisableInt();

    framep = __osViNext->framep;

    __osRestoreInt(saveMask);

    return framep;
}

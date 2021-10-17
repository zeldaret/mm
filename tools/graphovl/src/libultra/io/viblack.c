#include "global.h"

void osViBlack(u8 active) {
    register u32 saveMask;

    saveMask = __osDisableInt();

    if (active) {
        __osViNext->state |= 0x20;
    } else {
        __osViNext->state &= 0xffdf;
    }

    __osRestoreInt(saveMask);
}

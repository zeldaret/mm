#include "global.h"

void osViSetSpecialFeatures(u32 func) {
    register u32 saveMask = __osDisableInt();

    if (func & 1) {
        __osViNext->features |= 8;
    }
    if (func & 2) {
        __osViNext->features &= ~8;
    }
    if (func & 4) {
        __osViNext->features |= 4;
    }
    if (func & 8) {

        __osViNext->features &= ~4;
    }
    if (func & 0x10) {

        __osViNext->features |= 0x10;
    }
    if (func & 0x20) {

        __osViNext->features &= ~0x10;
    }
    if (func & 0x40) {
        __osViNext->features |= 0x10000;
        __osViNext->features &= ~0x300;
    }
    if (func & 0x80) {
        __osViNext->features &= ~0x10000;
        __osViNext->features |= __osViNext->modep->comRegs.ctrl & 0x300;
    }
    __osViNext->state |= 8;

    __osRestoreInt(saveMask);
}

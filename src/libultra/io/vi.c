#include "global.h"

void __osViInit(void) {
    bzero(D_80098060, sizeof(D_80098060));
    __osViCurr = &D_80098060[0];
    __osViNext = &D_80098060[1];
    __osViNext->retraceCount = 1;
    __osViCurr->retraceCount = 1;
    __osViNext->buffer = (void*)0x80000000;
    __osViCurr->buffer = (void*)0x80000000;

    if (osTvType == OS_TV_PAL) {
        __osViNext->modep = &osViModePalLan1;
    } else if (osTvType == OS_TV_MPAL) {
        __osViNext->modep = &osViModeMpalLan1;
    } else { // OS_TV_NTSC or OS_TV_UNK28
        __osViNext->modep = &osViModeNtscLan1;
    }

    __osViNext->state = 0x20;
    __osViNext->features = __osViNext->modep->comRegs.ctrl;

    while (HW_REG(VI_CURRENT_REG, u32) > 10) {
        ;
    }
    HW_REG(VI_STATUS_REG, u32) = 0;

    __osViSwapContext();
}

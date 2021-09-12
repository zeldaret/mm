#include "global.h"

void __osViInit(void) {
    bzero(D_80098060, sizeof(D_80098060));
    __osViCurr = &D_80098060[0];
    __osViNext = &D_80098060[1];
    __osViNext->retraceCount = 1;
    __osViCurr->retraceCount = 1;
    __osViNext->framep = (void*)0x80000000;
    __osViCurr->framep = (void*)0x80000000;

    if (osTvType == 0) {
        __osViNext->modep = &osViModePalLan1;
    } else if (osTvType == 2) {
        __osViNext->modep = &osViModeMpalLan1;
    } else {
        __osViNext->modep = &osViModeNtscLan1;
    }

    __osViNext->state = 0x20;
    __osViNext->control = __osViNext->modep->comRegs.ctrl;

    while (HW_REG(VI_CURRENT_REG, u32) > 10) {

    }
    HW_REG(VI_STATUS_REG, u32) = 0;

    __osViSwapContext();
}

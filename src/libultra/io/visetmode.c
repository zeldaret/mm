#include "global.h"

void osViSetMode(OSViMode* modep) {
    register u32 saveMask;

    saveMask = __osDisableInt();

    __osViNext->modep = modep;
    __osViNext->state = 1;
    __osViNext->features = __osViNext->modep->comRegs.ctrl;

    __osRestoreInt(saveMask);
}

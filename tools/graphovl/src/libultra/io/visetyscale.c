#include "global.h"

void osViSetYScale(f32 value) {
    register u32 saveMask;

    saveMask = __osDisableInt();

    __osViNext->y.factor = value;

    __osViNext->state |= 0x4;

    __osRestoreInt(saveMask);
}

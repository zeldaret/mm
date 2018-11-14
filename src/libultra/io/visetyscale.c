#include <stdarg.h>
#include <osint.h>
#include <viint.h>
#include <assert.h>

void osViSetYScale(f32 f12) {
    register u32 saveMask;

    saveMask = __osDisableInt();

    __osViNext->y.factor = f12;

    __osViNext->state |= 0x4;

    __osRestoreInt(saveMask);
}

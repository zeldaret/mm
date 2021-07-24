#include "ultra64.h"
#include "global.h"

s32 osContSetCh(u8 ch) {
    __osSiGetAccess();

    if (4 < ch) {
        __osMaxControllers = 4;
    } else {
        __osMaxControllers = ch;
    }
    __osContLastCmd = -2;

    __osSiRelAccess();
    return 0;
}

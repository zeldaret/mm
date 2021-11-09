#include "global.h"

s32 osContSetCh(u8 ch) {
    __osSiGetAccess();

    if (4 < ch) {
        __osMaxControllers = 4;
    } else {
        __osMaxControllers = ch;
    }
    __osContLastCmd = CONT_CMD_END;

    __osSiRelAccess();
    return 0;
}

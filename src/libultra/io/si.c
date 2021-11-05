#include "global.h"

s32 __osSiDeviceBusy() {
    register u32 status = HW_REG(SI_STATUS_REG, u32);

    if (status & 3) {
        return true;
    } else {
        return false;
    }
}

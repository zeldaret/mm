#include "global.h"

u32 osDpGetStatus(void) {
    return HW_REG(DPC_STATUS_REG, u32);
}

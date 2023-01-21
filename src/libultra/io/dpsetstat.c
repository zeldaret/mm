#include "global.h"

void osDpSetStatus(u32 data) {
    HW_REG(DPC_STATUS_REG, u32) = data;
}

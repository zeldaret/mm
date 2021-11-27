#include "global.h"

void __osSpSetStatus(u32 data) {
    HW_REG(SP_STATUS_REG, u32) = data;
}

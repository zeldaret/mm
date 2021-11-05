#include "global.h"

s32 __osPiRawStartDma(s32 direction, u32 devAddr, void* dramAddr, size_t size) {
    register int status;

    status = HW_REG(PI_STATUS_REG, u32);
    while (status & (PI_STATUS_IOBUSY | PI_STATUS_BUSY)) {
        status = HW_REG(PI_STATUS_REG, u32);
    }

    HW_REG(PI_DRAM_ADDR_REG, u32) = osVirtualToPhysical(dramAddr);

    HW_REG(PI_CART_ADDR_REG, u32) = ((osRomBase | devAddr) & 0x1FFFFFFF);

    switch (direction) {
        case OS_READ:
            HW_REG(PI_WR_LEN_REG, u32) = size - 1;
            break;
        case OS_WRITE:
            HW_REG(PI_RD_LEN_REG, u32) = size - 1;
            break;
        default:
            return -1;
    }
    return 0;
}

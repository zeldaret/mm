#include "global.h"

s32 __osSiRawStartDma(s32 direction, void* dramAddr) {
    if (HW_REG(SI_STATUS_REG, u32) & (SI_STATUS_DMA_BUSY | SI_STATUS_IO_READ_BUSY)) {
        return -1;
    }

    if (direction == OS_WRITE) {
        osWritebackDCache(dramAddr, 0x40);
    }

    HW_REG(SI_DRAM_ADDR_REG, u32) = osVirtualToPhysical(dramAddr);

    if (direction == OS_READ) {
        HW_REG(SI_PIF_ADDR_RD64B_REG, void*) = (void*)PIF_RAM_START;
    } else {
        HW_REG(SI_PIF_ADDR_WR64B_REG, void*) = (void*)PIF_RAM_START;
    }

    if (direction == OS_READ) {
        osInvalDCache(dramAddr, 0x40);
    }
    return 0;
}

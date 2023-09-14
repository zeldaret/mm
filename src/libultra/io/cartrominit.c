#include "global.h"

OSPiHandle __CartRomHandle;

OSPiHandle* osCartRomInit(void) {
    register u32 initialConfig;
    register s32 status;
    register u32 prevInt;
    register u32 lastLatency;
    register u32 lastPageSize;
    register u32 lastRelDuration;
    register u32 lastPulse;

    static s32 sCartRomNeedsInit = true;

    __osPiGetAccess();

    if (!sCartRomNeedsInit) {
        __osPiRelAccess();
        return &__CartRomHandle;
    }

    sCartRomNeedsInit = false;
    __CartRomHandle.type = DEVICE_TYPE_CART;
    __CartRomHandle.baseAddress = 0xB0000000;
    __CartRomHandle.domain = 0;
    __CartRomHandle.speed = 0;
    bzero(&__CartRomHandle.transferInfo, sizeof(__OSTranxInfo));

    /* Uses `status & PI_STATUS_ERROR` in OoT */
    while (status = HW_REG(PI_STATUS_REG, u32), status & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) {
        ;
    }

    lastLatency = HW_REG(PI_BSD_DOM1_LAT_REG, u32);
    lastPageSize = HW_REG(PI_BSD_DOM1_PGS_REG, u32);
    lastRelDuration = HW_REG(PI_BSD_DOM1_RLS_REG, u32);
    lastPulse = HW_REG(PI_BSD_DOM1_PWD_REG, u32);

    HW_REG(PI_BSD_DOM1_LAT_REG, u32) = 0xFF;
    HW_REG(PI_BSD_DOM1_PGS_REG, u32) = 0;
    HW_REG(PI_BSD_DOM1_RLS_REG, u32) = 3;
    HW_REG(PI_BSD_DOM1_PWD_REG, u32) = 0xFF;

    initialConfig = HW_REG(__CartRomHandle.baseAddress, u32);
    __CartRomHandle.latency = initialConfig & 0xFF;
    __CartRomHandle.pageSize = (initialConfig >> 0x10) & 0xF;
    __CartRomHandle.relDuration = (initialConfig >> 0x14) & 0xF;
    __CartRomHandle.pulse = (initialConfig >> 8) & 0xFF;

    HW_REG(PI_BSD_DOM1_LAT_REG, u32) = lastLatency;
    HW_REG(PI_BSD_DOM1_PGS_REG, u32) = lastPageSize;
    HW_REG(PI_BSD_DOM1_RLS_REG, u32) = lastRelDuration;
    HW_REG(PI_BSD_DOM1_PWD_REG, u32) = lastPulse;

    prevInt = __osDisableInt();
    __CartRomHandle.next = __osPiTable;
    __osPiTable = &__CartRomHandle;
    __osRestoreInt(prevInt);
    __osPiRelAccess();

    return &__CartRomHandle;
}

#include "global.h"

OSPiHandle CartRomHandle;

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
        return &CartRomHandle;
    }

    sCartRomNeedsInit = false;
    CartRomHandle.type = DEVICE_TYPE_CART;
    CartRomHandle.baseAddress = 0xB0000000;
    CartRomHandle.domain = 0;
    CartRomHandle.speed = 0;
    bzero(&CartRomHandle.transferInfo, sizeof(__OSTranxInfo));

    /* Uses `status & PI_STATUS_ERROR` in OoT */
    while (status = HW_REG(PI_STATUS_REG, u32), status & (PI_STATUS_BUSY | PI_STATUS_IOBUSY)) {
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

    initialConfig = HW_REG(CartRomHandle.baseAddress, u32);
    CartRomHandle.latency = initialConfig & 0xFF;
    CartRomHandle.pageSize = (initialConfig >> 0x10) & 0xF;
    CartRomHandle.relDuration = (initialConfig >> 0x14) & 0xF;
    CartRomHandle.pulse = (initialConfig >> 8) & 0xFF;

    HW_REG(PI_BSD_DOM1_LAT_REG, u32) = lastLatency;
    HW_REG(PI_BSD_DOM1_PGS_REG, u32) = lastPageSize;
    HW_REG(PI_BSD_DOM1_RLS_REG, u32) = lastRelDuration;
    HW_REG(PI_BSD_DOM1_PWD_REG, u32) = lastPulse;

    prevInt = __osDisableInt();
    CartRomHandle.next = __osPiTable;
    __osPiTable = &CartRomHandle;
    __osRestoreInt(prevInt);
    __osPiRelAccess();

    return &CartRomHandle;
}

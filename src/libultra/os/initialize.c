#include "global.h"

#define COLD_RESET 0

typedef struct {
    /* 0x0 */ u32 ins_00; // lui     k0, 0x8000
    /* 0x4 */ u32 ins_04; // addiu   k0, k0, 0x39E0
    /* 0x8 */ u32 ins_08; // jr      k0 ; __osException
    /* 0xC */ u32 ins_0C; // nop
} __osExceptionVector;    // size = 0x10

extern __osExceptionVector __osExceptionPreamble;

u64 osClockRate = OS_CLOCK_RATE;
s32 osViClock = VI_NTSC_CLOCK;
u32 __osShutdown = 0;
u32 __OSGlobalIntMask = 0x003FFF01;

u32 __osFinalrom;

void __createSpeedParam(void) {
    __Dom1SpeedParam.type = DEVICE_TYPE_INIT;
    __Dom1SpeedParam.latency = HW_REG(PI_BSD_DOM1_LAT_REG, u32);
    __Dom1SpeedParam.pulse = HW_REG(PI_BSD_DOM1_PWD_REG, u32);
    __Dom1SpeedParam.pageSize = HW_REG(PI_BSD_DOM1_PGS_REG, u32);
    __Dom1SpeedParam.relDuration = HW_REG(PI_BSD_DOM1_RLS_REG, u32);

    __Dom2SpeedParam.type = DEVICE_TYPE_INIT;
    __Dom2SpeedParam.latency = HW_REG(PI_BSD_DOM2_LAT_REG, u32);
    __Dom2SpeedParam.pulse = HW_REG(PI_BSD_DOM2_PWD_REG, u32);
    __Dom2SpeedParam.pageSize = HW_REG(PI_BSD_DOM2_PGS_REG, u32);
    __Dom2SpeedParam.relDuration = HW_REG(PI_BSD_DOM2_RLS_REG, u32);
}

void __osInitialize_common(void) {
    u32 pifdata;

    __osFinalrom = 1;

    __osSetSR(__osGetSR() | 0x20000000);
    __osSetFpcCsr(0x01000800);
    __osSetWatchLo(0x04900000);

    while (__osSiRawReadIo(0x1FC007FC, &pifdata)) {}

    while (__osSiRawWriteIo(0x1FC007FC, pifdata | 8)) {}

    *(__osExceptionVector*)0x80000000 = __osExceptionPreamble;
    *(__osExceptionVector*)0x80000080 = __osExceptionPreamble;
    *(__osExceptionVector*)0x80000100 = __osExceptionPreamble;
    *(__osExceptionVector*)0x80000180 = __osExceptionPreamble;

    osWritebackDCache((void*)0x80000000, 400);
    osInvalICache((void*)0x80000000, 400);
    __createSpeedParam();
    osUnmapTLBAll();
    osMapTLBRdb();

    osClockRate = (u64)((osClockRate * 3LL) / 4ULL);

    if (osResetType == COLD_RESET) {
        bzero(osAppNMIBuffer, 64);
    }

    if (osTvType == OS_TV_PAL) {
        osViClock = VI_PAL_CLOCK;
    } else if (osTvType == OS_TV_MPAL) {
        osViClock = VI_MPAL_CLOCK;
    } else {
        osViClock = VI_NTSC_CLOCK;
    }

    if (__osGetCause() & 0x1000) {
        while (true) {}
    }

    HW_REG(AI_CONTROL_REG, u32) = 1;
    HW_REG(AI_DACRATE_REG, u32) = 0x3FFF;
    HW_REG(AI_BITRATE_REG, u32) = 0xF;
}

void __osInitialize_autodetect(void) {
}

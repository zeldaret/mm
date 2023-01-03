#include "global.h"

#define COLD_RESET 0

typedef struct {
    /* 0x0 */ u32 ins_00; // lui     k0, 0x8000
    /* 0x4 */ u32 ins_04; // addiu   k0, k0, 0x39E0
    /* 0x8 */ u32 ins_08; // jr      k0 ; __osException
    /* 0xC */ u32 ins_0C; // nop
} struct_exceptionPreamble;

u64 osClockRate = OS_CLOCK_RATE;
s32 osViClock = VI_NTSC_CLOCK;
UNK_TYPE4 __osShutdown = 0;
UNK_TYPE4 __OSGlobalIntMask = 0x003FFF01;

UNK_TYPE4 D_8009CF70;

void __createSpeedParam(void) {
    D_8009D130.type = DEVICE_TYPE_INIT;
    D_8009D130.latency = HW_REG(PI_BSD_DOM1_LAT_REG, u32);
    D_8009D130.pulse = HW_REG(PI_BSD_DOM1_PWD_REG, u32);
    D_8009D130.pageSize = HW_REG(PI_BSD_DOM1_PGS_REG, u32);
    D_8009D130.relDuration = HW_REG(PI_BSD_DOM1_RLS_REG, u32);

    D_8009D1A8.type = DEVICE_TYPE_INIT;
    D_8009D1A8.latency = HW_REG(PI_BSD_DOM2_LAT_REG, u32);
    D_8009D1A8.pulse = HW_REG(PI_BSD_DOM2_PWD_REG, u32);
    D_8009D1A8.pageSize = HW_REG(PI_BSD_DOM2_PGS_REG, u32);
    D_8009D1A8.relDuration = HW_REG(PI_BSD_DOM2_RLS_REG, u32);
}

void osInitialize(void) {
    u32 pifdata;

    D_8009CF70 = 1;

    __osSetSR(__osGetSR() | 0x20000000);
    __osSetFpcCsr(0x01000800);
    __osSetWatchLo(0x04900000);

    while (__osSiRawReadIo(0x1FC007FC, &pifdata)) {
        ;
    }
    while (__osSiRawWriteIo(0x1FC007FC, pifdata | 8)) {
        ;
    }

    *(struct_exceptionPreamble*)0x80000000 = *((struct_exceptionPreamble*)__osExceptionPreamble);
    *(struct_exceptionPreamble*)0x80000080 = *((struct_exceptionPreamble*)__osExceptionPreamble);
    *(struct_exceptionPreamble*)0x80000100 = *((struct_exceptionPreamble*)__osExceptionPreamble);
    *(struct_exceptionPreamble*)0x80000180 = *((struct_exceptionPreamble*)__osExceptionPreamble);

    osWritebackDCache(0x80000000, 400);
    osInvalICache(0x80000000, 400);
    __createSpeedParam();
    osUnmapTLBAll();
    osMapTLBRdb();

    osClockRate = (u64)((osClockRate * 3LL) / 4ULL);

    if (osResetType == COLD_RESET) {
        bzero(osAppNmiBuffer, 64);
    }

    if (osTvType == OS_TV_PAL) {
        osViClock = VI_PAL_CLOCK;
    } else if (osTvType == OS_TV_MPAL) {
        osViClock = VI_MPAL_CLOCK;
    } else {
        osViClock = VI_NTSC_CLOCK;
    }

    if (__osGetCause() & 0x1000) {
        while (1) {
            ;
        }
    }

    HW_REG(AI_CONTROL_REG, u32) = 1;
    HW_REG(AI_DACRATE_REG, u32) = 0x3FFF;
    HW_REG(AI_BITRATE_REG, u32) = 0xF;
}

void __osInitialize_autodetect(void) {
}

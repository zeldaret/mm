#include <ultra64.h>
#include <global.h>

u64 osClockRate = 0x0000000003B9ACA0;
s32 osViClock = 0x02E6D354;
UNK_TYPE4 __osShutdown = 0;
UNK_TYPE4 __OSGlobalIntMask = 0x003FFF01;

void func_8008A660(void) {
    D_8009D130.type = 7;
    D_8009D130.latency = *(u32*)0xA4600014;
    D_8009D130.pageSize = *(u32*)0xA4600018;
    D_8009D130.relDuration = *(u32*)0xA460001C;
    D_8009D130.pulse = *(u32*)0xA4600020;
    D_8009D1A8.type = 7;
    D_8009D1A8.latency = *(u32*)0xA4600024;
    D_8009D1A8.pageSize = *(u32*)0xA4600028;
    D_8009D1A8.relDuration = *(u32*)0xA460002C;
    D_8009D1A8.pulse = *(u32*)0xA4600030;
}

u64 D_80097E50; // this has to be defined in this file for func_8008A6FC to match

// TODO regalloc is messed up here
// TODO When asm-processor supports -O1, use it here
void osInitialize(void) {
    u32 pifdata;

    D_8009CF70 = 1;

    __osSetSR(__osGetSR() | 0x20000000);
    __osSetFpcCsr(0x01000800);
    __osSetWatchLo(0x04900000);

    while (__osSiRawReadIo(0x1FC007FC, &pifdata) != 0) {
        ;
    }
    while (__osSiRawWriteIo(0x1FC007FC, pifdata | 8) != 0) {
        ;
    }

    *(__osExceptionVector*)0x80000000 = *((__osExceptionVector*)__osExceptionPreamble);
    *(__osExceptionVector*)0x80000080 = *((__osExceptionVector*)__osExceptionPreamble);
    *(__osExceptionVector*)0x80000100 = *((__osExceptionVector*)__osExceptionPreamble);
    *(__osExceptionVector*)0x80000180 = *((__osExceptionVector*)__osExceptionPreamble);

    osWritebackDCache((void*)0x80000000, 400);
    osInvalICache((void*)0x80000000, 400);
    func_8008A660();
    osUnmapTLBAll();
    osMapTLBRdb();
    D_80097E50 = (D_80097E50 * 3) / 4;

    if (osResetType == 0) {
        _blkclr((u8*)&osAppNmiBuffer, 64);
    }

    if (osTvType == 0) {
        osViClock = 0x02F5B2D2;
    } else if (osTvType == 2) {
        osViClock = 0x02E6025C;
    } else {
        osViClock = 0x02E6D354;
    }

    if ((__osGetCause() & 0x1000) != 0) {
        while (1) {
            ;
        }
    }

    *(u32*)0xA4500008 = 1;
    *(u32*)0xA4500010 = 16383;
    *(u32*)0xA4500014 = 15;
}

void func_8008A9A8(void) {
}

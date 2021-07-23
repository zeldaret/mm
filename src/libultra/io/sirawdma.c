#include "ultra64.h"
#include "global.h"

s32 __osSiRawStartDma(s32 direction, void* dramAddr) {
    if ((*(u32*)0xA4800018 & 0x3) != 0) {
        return -1;
    }

    if (direction == 1) {
        osWritebackDCache(dramAddr, 64);
    }

    *(u32*)0xA4800000 = osVirtualToPhysical(dramAddr);

    if (direction == 0) {
        *(u32*)0xA4800004 = 0x1FC007C0;
    } else {
        *(u32*)0xA4800010 = 0x1FC007C0;
    }

    if (direction == 0) {
        osInvalDCache(dramAddr, 64);
    }
    return 0;
}

#include <ultra64.h>
#include <global.h>

s32 osPiRawStartDma(s32 direction, u32 devAddr, void* dramAddr, u32 size) {
    register int stat;

    stat = *(vu32*)0xA4600010;
    while (stat & (2 | 1)) {
        stat = *(vu32*)0xA4600010;
    }

    *(u32*)0xA4600000 = osVirtualToPhysical(dramAddr);

    *(u32*)0xA4600004 = ((osRomBase | devAddr) & 0x1fffffff);

    switch (direction) {
        case 0:
            *(u32*)0xA460000C = size - 1;
            break;
        case 1:
            *(u32*)0xA4600008 = size - 1;
            break;
        default:
            return -1;
    }
    return 0;
}

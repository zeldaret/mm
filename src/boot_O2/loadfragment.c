#include "global.h"
#include "system_malloc.h"

s32 D_80096C20 = 2;

#define NON_MATCHING
#ifdef NON_MATCHING
void Load_Relocate(void* allocatedVRamAddr, OverlayRelocationSection* overlayInfo, u32 vRamStart) {
    s32 sectionLocations[4];
    u32* regReferences[32];
    u32 regValues[32];
    u32 i;
    u32 relocatedAddress;
    s32 signedOffset;
    u32* lastInst;
    u32* inst;
    u32 relocation;
    u32 relocationIndex;

    sectionLocations[0] = 0;
    sectionLocations[1] = (uintptr_t)allocatedVRamAddr;
    sectionLocations[2] = overlayInfo->textSize + (uintptr_t)allocatedVRamAddr;
    sectionLocations[3] = sectionLocations[2] + overlayInfo->dataSize;
    for (i = 0, relocationIndex = 0; i < overlayInfo->nRelocations; relocationIndex++) {
        relocation = overlayInfo->relocations[relocationIndex];
        i++;
        inst = (u32*)(sectionLocations[relocation >> 0x1e] + (relocation & 0xffffff));

        switch (relocation & 0x3f000000) {
            case 0x2000000:
                if ((*inst & 0xf000000) == 0) {
                    *inst = (*inst - vRamStart) + (uintptr_t)allocatedVRamAddr;
                } else {
                    if (D_80096C20 > 2) {}
                }
                break;
            case 0x4000000:
                *inst = (*inst & 0xfc000000) |
                        ((((((*inst & 0x3ffffff) << 2 | 0x80000000) - vRamStart) + (uintptr_t)allocatedVRamAddr) &
                          0xfffffff) >>
                         2);
                break;
            case 0x5000000:
                regReferences[*inst >> 0x10 & 0x1f] = inst;
                regValues[*inst >> 0x10 & 0x1f] = *inst;
                break;
            case 0x6000000:
                lastInst = regReferences[*inst >> 0x15 & 0x1f];
                signedOffset = (s16)*inst;
                if (((signedOffset + *lastInst * 0x10000) & 0xf000000) == 0) {
                    relocatedAddress = ((signedOffset + regValues[*inst >> 0x15 & 0x1f] * 0x10000) - vRamStart) +
                                       (uintptr_t)allocatedVRamAddr;
                    *lastInst = (((relocatedAddress >> 0x10) & 0xFFFF) + ((relocatedAddress & 0x8000) ? 1 : 0)) |
                                (*lastInst & 0xffff0000);
                    *inst = (*inst & 0xffff0000) | (relocatedAddress & 0xffff);
                }
                break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/loadfragment/Load_Relocate.s")
#endif
#undef NON_MATCHING

#ifdef NON_MATCHING
// Small stack issue, compiler managed is too low
size_t Load_LoadOverlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, void* allocatedVRamAddr, size_t allocatedBytes) {
    s32 pad[2];
    size_t size = vRomEnd - vRomStart;
    OverlayRelocationSection* overlayInfo;
    void* end;

    if (1) {}
    if (1) {}

    DmaMgr_SendRequest0(allocatedVRamAddr, vRomStart, size);

    end = (uintptr_t)allocatedVRamAddr + size;
    overlayInfo = (OverlayRelocationSection*)((uintptr_t)end - ((s32*)end)[-1]);

    if (allocatedBytes < overlayInfo->bssSize + size) {
        return (overlayInfo->bssSize + size) * 0;
    }

    allocatedBytes = overlayInfo->bssSize + size;

    Load_Relocate(allocatedVRamAddr, overlayInfo, vRamStart);

    if (overlayInfo->bssSize != 0) {
        if (1) {}
        bzero(end, overlayInfo->bssSize);
    }

    osWritebackDCache(allocatedVRamAddr, allocatedBytes);
    osInvalICache(allocatedVRamAddr, allocatedBytes);

    if (1) {}

    return allocatedBytes;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/loadfragment/Load_LoadOverlay.s")
#endif

void* Load_AllocateAndLoad(u32 vRomStart, u32 vRomEnd, u32 vRamStart) {
    size_t size = vRomEnd - vRomStart;
    void* end;
    void* allocatedVRamAddr;
    uintptr_t ovlOffset;
    OverlayRelocationSection* overlayInfo;
    size_t bssSize;

    if (1) {}

    allocatedVRamAddr = SystemArena_MallocR(size);
    end = (uintptr_t)allocatedVRamAddr + size;

    DmaMgr_SendRequest0(allocatedVRamAddr, vRomStart, size);

    if (1) {}

    ovlOffset = (uintptr_t)end - 4;
    overlayInfo = (OverlayRelocationSection*)((uintptr_t)end - ((s32*)end)[-1]);

    if (allocatedVRamAddr && allocatedVRamAddr) {}

    bssSize = overlayInfo->bssSize + size;

    allocatedVRamAddr = SystemArena_Realloc(allocatedVRamAddr, bssSize);

    if (1) {}

    if (allocatedVRamAddr == NULL) {
        if (1) {}
        return allocatedVRamAddr;
    }

    end = (uintptr_t)allocatedVRamAddr + size;
    overlayInfo = (OverlayRelocationSection*)((uintptr_t)end - *(uintptr_t*)ovlOffset);

    if (1) {}

    Load_Relocate(allocatedVRamAddr, overlayInfo, vRamStart);

    if (overlayInfo->bssSize != 0) {
        if (1) {}
        bzero(end, overlayInfo->bssSize);
    }

    osInvalICache(allocatedVRamAddr, bssSize);

    if (1) {}

    return allocatedVRamAddr;
}

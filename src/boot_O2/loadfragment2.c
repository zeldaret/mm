#include "global.h"
#include "system_malloc.h"

UNK_TYPE4 D_80096C30 = 2;

#ifdef NON_MATCHING
// This needs lots of work. Mostly regalloc and getting the address of D_80096C30 placed in s5 at the beginning of the
// function
void Load2_Relocate(u32 allocatedVRamAddr, OverlayRelocationSection* overlayInfo, u32 vRamStart) {
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
    sectionLocations[1] = allocatedVRamAddr;
    sectionLocations[2] = overlayInfo->textSize + allocatedVRamAddr;
    sectionLocations[3] = sectionLocations[2] + overlayInfo->dataSize;
    for (i = 0, relocationIndex = 0; i < overlayInfo->nRelocations; relocationIndex++) {
        relocation = overlayInfo->relocations[relocationIndex];
        i++;
        inst = (u32*)(sectionLocations[relocation >> 0x1e] + (relocation & 0xffffff));

        switch (relocation & 0x3f000000) {
            case 0x2000000:
                if ((*inst & 0xf000000) == 0) {
                    *inst = (*inst - vRamStart) + allocatedVRamAddr;
                }
                /*
                else {
                    if (D_80096C30 > 2) {
                        ;
                    }
                }
                */
                break;
            case 0x4000000:
                *inst =
                    (*inst & 0xfc000000) |
                    ((((((*inst & 0x3ffffff) << 2 | 0x80000000) - vRamStart) + allocatedVRamAddr) & 0xfffffff) >> 2);
                break;
            case 0x5000000:
                regReferences[*inst >> 0x10 & 0x1f] = inst;
                regValues[*inst >> 0x10 & 0x1f] = *inst;
                break;
            case 0x6000000:
                lastInst = regReferences[*inst >> 0x15 & 0x1f];
                signedOffset = (s16)*inst;
                if (((signedOffset + *lastInst * 0x10000) & 0xf000000) == 0) {
                    relocatedAddress =
                        ((signedOffset + regValues[*inst >> 0x15 & 0x1f] * 0x10000) - vRamStart) + allocatedVRamAddr;
                    *lastInst = (((relocatedAddress >> 0x10) & 0xFFFF) + ((relocatedAddress & 0x8000) ? 1 : 0)) |
                                (*lastInst & 0xffff0000);
                    *inst = (*inst & 0xffff0000) | (relocatedAddress & 0xffff);
                }
                break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/loadfragment2/Load2_Relocate.s")
#endif

#ifdef NON_MATCHING
// Very minor stack stuff with a saved value
s32 Load2_LoadOverlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd, u32 allocatedVRamAddr) {
    int nbytes;
    u32 pad;
    size_t size;
    void* end;
    OverlayRelocationSection* overlayInfo;

    size = vRomEnd - vRomStart;

    if (1) {
        ;
    }

    DmaMgr_SendRequest0(allocatedVRamAddr, vRomStart, size);

    end = (void*)(allocatedVRamAddr + size);
    overlayInfo = (OverlayRelocationSection*)((int)end - *(int*)((int)end + -4));

    if (1) {
        ;
    }

    Load2_Relocate(allocatedVRamAddr, overlayInfo, vRamStart);

    if (overlayInfo->bssSize != 0) {
        bzero(end, overlayInfo->bssSize);
    }

    nbytes = vRamEnd - vRamStart;

    osWritebackDCache((void*)allocatedVRamAddr, nbytes);
    osInvalICache((void*)allocatedVRamAddr, nbytes);
    return nbytes;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/loadfragment2/Load2_LoadOverlay.s")
#endif

void* Overlay_AllocateAndLoad(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd) {
    void* allocatedVRamAddr;
    size_t size;

    size = vRamEnd - vRamStart;
    allocatedVRamAddr = SystemArena_MallocR(size);
    if (allocatedVRamAddr != NULL) {
        Load2_LoadOverlay(vRomStart, vRomEnd, vRamStart, vRamEnd, (u32)allocatedVRamAddr);
    }

    return allocatedVRamAddr;
}

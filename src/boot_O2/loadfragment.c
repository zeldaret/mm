#include "global.h"
#include "system_malloc.h"

s32 D_80096C20 = 2;

#ifdef NON_MATCHING
// Mostly regalloc and getting the address of D_80096C20 placed in s5 at the beginning of the function
void Load_Relocate(void* allocatedVRamAddr, OverlayRelocationSection* ovl, u32 vRamStart) {
    u32 sections[4];
    u32* relocDataP;
    u32 reloc;
    u32 relocatedAddress;
    u32 i;
    u32* luiInstRef;
    u32* luiRefs[32];
    u32 luiVals[32];
    uintptr_t allocu32 = (uintptr_t)allocatedVRamAddr;
    u32* regValP;
    u32 isLoNeg;
    s32 signedOffset;

    sections[0] = 0;
    sections[1] = allocu32;
    sections[2] = allocu32 + ovl->textSize;
    sections[3] = sections[2] + ovl->dataSize;

    for (i = 0; i < ovl->nRelocations; i++) {
        reloc = ovl->relocations[i];
        relocDataP = (u32*)(sections[reloc >> 0x1E] + (reloc & 0xFFFFFF));

        switch (reloc & 0x3F000000) {
            case 0x2000000:
                /* R_MIPS_32
                 * Handles 32-bit address relocation.  Used in things such as
                 * jump tables.
                 */
                if ((*relocDataP & 0xF000000) == 0) {
                    *relocDataP = (*relocDataP - vRamStart) + allocu32;
                } else {
                    if (D_80096C20 >= 3) {}
                }
                break;
            case 0x4000000:
                /* R_MIPS_26
                 * Handles 26-bit address relocation, used for jumps and jals
                 */
                *relocDataP =
                    (*relocDataP & 0xFC000000) |
                    (((allocu32 + ((((*relocDataP & 0x3FFFFFF) << 2) | 0x80000000) - vRamStart)) & 0xFFFFFFF) >> 2);
                break;
            case 0x5000000:
                /* R_MIPS_HI16
                 * Handles relocation for a lui instruciton, store the reference to
                 * the instruction, and will update it in the R_MIPS_LO16 section.
                 */
                luiRefs[(*relocDataP >> 0x10) & 0x1F] = relocDataP;
                luiVals[(*relocDataP >> 0x10) & 0x1F] = *relocDataP;
                break;
            case 0x6000000:
                /* R_MIPS_LO16
                 * Updates the LUI instruction to reflect the relocated address.
                 * The full address is calculated from the LUI and lo parts, and then updated.
                 * if the lo part is negative, add 1 to the lui.
                 */
                luiInstRef = luiRefs[(*relocDataP >> 0x15) & 0x1F];
                signedOffset = (s16)*relocDataP;
                if (((signedOffset + (*luiInstRef << 0x10)) & 0x0F000000) == 0) {
                    relocatedAddress =
                        ((signedOffset + (luiVals[(*relocDataP >> 0x15) & 0x1F] << 0x10)) - vRamStart) + allocu32;
                    isLoNeg = (relocatedAddress & 0x8000) ? 1 : 0;
                    *luiInstRef = (*luiInstRef & 0xFFFF0000) | (((relocatedAddress >> 0x10) & 0xFFFF) + isLoNeg);
                    *relocDataP = (*relocDataP & 0xFFFF0000) | (relocatedAddress & 0xFFFF);
                }
                break;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/loadfragment/Load_Relocate.s")
#endif

#ifdef NON_MATCHING
// Small stack issue, compiler managed is too low
size_t Load_LoadOverlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, void* allocatedVRamAddr, size_t allocatedBytes) {
    s32 pad[2];
    size_t size = vRomEnd - vRomStart;
    OverlayRelocationSection* ovl;
    void* end;

    if (1) {}
    if (1) {}

    DmaMgr_SendRequest0(allocatedVRamAddr, vRomStart, size);

    end = (uintptr_t)allocatedVRamAddr + size;
    ovl = (OverlayRelocationSection*)((uintptr_t)end - ((s32*)end)[-1]);

    if (allocatedBytes < ovl->bssSize + size) {
        return (ovl->bssSize + size) * 0;
    }

    allocatedBytes = ovl->bssSize + size;

    Load_Relocate(allocatedVRamAddr, ovl, vRamStart);

    if (ovl->bssSize != 0) {
        if (1) {}
        bzero(end, ovl->bssSize);
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
    OverlayRelocationSection* ovl;
    size_t bssSize;

    if (1) {}

    allocatedVRamAddr = SystemArena_MallocR(size);
    end = (uintptr_t)allocatedVRamAddr + size;

    DmaMgr_SendRequest0(allocatedVRamAddr, vRomStart, size);

    if (1) {}

    ovlOffset = (uintptr_t)end - 4;
    ovl = (OverlayRelocationSection*)((uintptr_t)end - ((s32*)end)[-1]);

    if (allocatedVRamAddr && allocatedVRamAddr) {}

    bssSize = ovl->bssSize + size;

    allocatedVRamAddr = SystemArena_Realloc(allocatedVRamAddr, bssSize);

    if (1) {}

    if (allocatedVRamAddr == NULL) {
        if (1) {}
        return allocatedVRamAddr;
    }

    end = (uintptr_t)allocatedVRamAddr + size;
    ovl = (OverlayRelocationSection*)((uintptr_t)end - *(uintptr_t*)ovlOffset);

    if (1) {}

    Load_Relocate(allocatedVRamAddr, ovl, vRamStart);

    if (ovl->bssSize != 0) {
        if (1) {}
        bzero(end, ovl->bssSize);
    }

    osInvalICache(allocatedVRamAddr, bssSize);

    if (1) {}

    return allocatedVRamAddr;
}

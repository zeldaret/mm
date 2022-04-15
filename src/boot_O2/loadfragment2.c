#include "global.h"
#include "system_malloc.h"

s32 D_80096C30 = 2;

#ifdef NON_MATCHING
// Mostly regalloc and getting the address of D_80096C30 placed in s5 at the beginning of the function
void Load2_Relocate(void* allocatedVRamAddr, OverlayRelocationSection* ovl, u32 vRamStart) {
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
                    if (D_80096C30 >= 3) {}
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
#pragma GLOBAL_ASM("asm/non_matchings/boot/loadfragment2/Load2_Relocate.s")
#endif

size_t Load2_LoadOverlay(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd, void* allocatedVRamAddr) {
    s32 pad[2];
    size_t size = vRomEnd - vRomStart;
    void* end;
    OverlayRelocationSection* ovl;

    if (1) {}

    end = (uintptr_t)allocatedVRamAddr + size;
    DmaMgr_SendRequest0(allocatedVRamAddr, vRomStart, size);

    ovl = (OverlayRelocationSection*)((uintptr_t)end - ((s32*)end)[-1]);

    if (ovl->bssSize && ovl->bssSize) {}

    Load2_Relocate(allocatedVRamAddr, ovl, vRamStart);

    if (ovl->bssSize != 0) {
        bzero(end, ovl->bssSize);
    }

    size = vRamEnd - vRamStart;

    osWritebackDCache(allocatedVRamAddr, size);
    osInvalICache(allocatedVRamAddr, size);

    return size;
}

void* Overlay_AllocateAndLoad(u32 vRomStart, u32 vRomEnd, u32 vRamStart, u32 vRamEnd) {
    void* allocatedVRamAddr = SystemArena_MallocR(vRamEnd - vRamStart);

    if (allocatedVRamAddr != NULL) {
        Load2_LoadOverlay(vRomStart, vRomEnd, vRamStart, vRamEnd, allocatedVRamAddr);
    }

    return allocatedVRamAddr;
}

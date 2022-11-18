/**
 * @file loadfragment.c
 *
 * Functions used to process and relocate overlays
 *
 * @note:
 *  These are completly unused in favor of the functions in `loadfragment2.c`.
 *
 *  The main difference between them seems to be the lack of vRamEnd arguments here.
 *  Instead they are calculated on the fly.
 */
#include "global.h"
#include "system_malloc.h"
#include "z64load.h"

s32 gLoadLogSeverity = 2;

void Load_Relocate(void* allocatedVRamAddr, OverlayRelocationSection* ovl, uintptr_t vRamStart) {
    u32 sections[4];
    u32* relocDataP;
    u32 reloc;
    uintptr_t relocatedAddress;
    u32 i;
    u32* luiInstRef;
    uintptr_t allocu32 = (uintptr_t)allocatedVRamAddr;
    u32* regValP;
    u32* luiRefs[32];
    u32 luiVals[32];
    u32 isLoNeg;

    if (gLoadLogSeverity >= 3) {}

    sections[0] = 0;
    sections[1] = allocu32;
    sections[2] = allocu32 + ovl->textSize;
    sections[3] = sections[2] + ovl->dataSize;

    for (i = 0; i < ovl->nRelocations; i++) {
        reloc = ovl->relocations[i];
        relocDataP = (u32*)(sections[RELOC_SECTION(reloc)] + RELOC_OFFSET(reloc));

        switch (RELOC_TYPE_MASK(reloc)) {
            case R_MIPS_32 << RELOC_TYPE_SHIFT:
                // Handles 32-bit address relocation, used for things such as jump tables and pointers in data.
                // Just relocate the full address

                // Check address is valid for relocation
                if ((*relocDataP & 0x0F000000) == 0) {
                    *relocDataP = RELOCATE_ADDR(*relocDataP, vRamStart, allocu32);
                } else if (gLoadLogSeverity >= 3) {
                }
                break;

            case R_MIPS_26 << RELOC_TYPE_SHIFT:
                // Handles 26-bit address relocation, used for jumps and jals.
                // Extract the address from the target field of the J-type MIPS instruction.
                // Relocate the address and update the instruction.

                *relocDataP =
                    (*relocDataP & 0xFC000000) |
                    ((RELOCATE_ADDR(PHYS_TO_K0((*relocDataP & 0x03FFFFFF) << 2), vRamStart, allocu32) & 0x0FFFFFFF) >>
                     2);
                break;

            case R_MIPS_HI16 << RELOC_TYPE_SHIFT:
                // Handles relocation for a hi/lo pair, part 1.
                // Store the reference to the LUI instruction (hi) using the `rt` register of the instruction.
                // This will be updated later in the `R_MIPS_LO16` section.

                luiRefs[(*relocDataP >> 0x10) & 0x1F] = relocDataP;
                luiVals[(*relocDataP >> 0x10) & 0x1F] = *relocDataP;
                break;

            case R_MIPS_LO16 << RELOC_TYPE_SHIFT:
                // Handles relocation for a hi/lo pair, part 2.
                // Grab the stored LUI (hi) from the `R_MIPS_HI16` section using the `rs` register of the instruction.
                // The full address is calculated, relocated, and then used to update both the LUI and lo instructions.
                // If the lo part is negative, add 1 to the LUI value.
                // Note: The lo instruction is assumed to have a signed immediate.

                luiInstRef = luiRefs[(*relocDataP >> 0x15) & 0x1F];
                regValP = &luiVals[(*relocDataP >> 0x15) & 0x1F];

                // Check address is valid for relocation
                if ((((*luiInstRef << 0x10) + (s16)*relocDataP) & 0x0F000000) == 0) {
                    relocatedAddress = RELOCATE_ADDR((*regValP << 0x10) + (s16)*relocDataP, vRamStart, allocu32);
                    isLoNeg = (relocatedAddress & 0x8000) ? 1 : 0;
                    *luiInstRef = (*luiInstRef & 0xFFFF0000) | (((relocatedAddress >> 0x10) & 0xFFFF) + isLoNeg);
                    *relocDataP = (*relocDataP & 0xFFFF0000) | (relocatedAddress & 0xFFFF);
                } else if (gLoadLogSeverity >= 3) {
                }
                break;
        }
    }
}

size_t Load_LoadOverlay(uintptr_t vRomStart, uintptr_t vRomEnd, uintptr_t vRamStart, void* allocatedVRamAddr,
                        size_t allocatedBytes) {
    size_t size = vRomEnd - vRomStart;
    uintptr_t end;
    s32 pad;
    OverlayRelocationSection* ovl;

    if (gLoadLogSeverity >= 3) {}
    if (gLoadLogSeverity >= 3) {}

    end = (uintptr_t)allocatedVRamAddr + size;
    DmaMgr_SendRequest0(allocatedVRamAddr, vRomStart, size);

    ovl = (OverlayRelocationSection*)(end - ((s32*)end)[-1]);

    if (gLoadLogSeverity >= 3) {}

    if (allocatedBytes < ovl->bssSize + size) {
        if (gLoadLogSeverity >= 3) {}
        return 0;
    }

    allocatedBytes = ovl->bssSize + size;

    if (gLoadLogSeverity >= 3) {}

    Load_Relocate(allocatedVRamAddr, ovl, vRamStart);

    if (ovl->bssSize != 0) {
        if (gLoadLogSeverity >= 3) {}
        bzero((void*)end, ovl->bssSize);
    }

    osWritebackDCache(allocatedVRamAddr, allocatedBytes);
    osInvalICache(allocatedVRamAddr, allocatedBytes);

    if (gLoadLogSeverity >= 3) {}

    return allocatedBytes;
}

void* Load_AllocateAndLoad(uintptr_t vRomStart, uintptr_t vRomEnd, uintptr_t vRamStart) {
    size_t size = vRomEnd - vRomStart;
    uintptr_t end;
    void* allocatedVRamAddr;
    uintptr_t ovlOffset;
    OverlayRelocationSection* ovl;
    size_t allocatedBytes;

    if (gLoadLogSeverity >= 3) {}

    allocatedVRamAddr = SystemArena_MallocR(size);
    end = (uintptr_t)allocatedVRamAddr + size;

    if (gLoadLogSeverity >= 3) {}

    DmaMgr_SendRequest0(allocatedVRamAddr, vRomStart, size);

    if (gLoadLogSeverity >= 3) {}

    ovlOffset = end - sizeof(s32);
    ovl = (OverlayRelocationSection*)(end - ((s32*)end)[-1]);

    if (1) {}

    allocatedBytes = ovl->bssSize + size;

    allocatedVRamAddr = SystemArena_Realloc(allocatedVRamAddr, allocatedBytes);

    if (gLoadLogSeverity >= 3) {}

    if (allocatedVRamAddr == NULL) {
        if (gLoadLogSeverity >= 3) {}
        return allocatedVRamAddr;
    }

    end = (uintptr_t)allocatedVRamAddr + size;
    ovl = (OverlayRelocationSection*)(end - *(uintptr_t*)ovlOffset);

    if (gLoadLogSeverity >= 3) {}

    Load_Relocate(allocatedVRamAddr, ovl, vRamStart);

    if (ovl->bssSize != 0) {
        if (gLoadLogSeverity >= 3) {}
        bzero((void*)end, ovl->bssSize);
    }

    osInvalICache(allocatedVRamAddr, allocatedBytes);

    if (gLoadLogSeverity >= 3) {}

    return allocatedVRamAddr;
}

#include "global.h"
#include "system_malloc.h"

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
        relocDataP = (u32*)(sections[reloc >> 0x1E] + (reloc & 0xFFFFFF));

        switch (reloc & 0x3F000000) {
            case 0x2000000:
                // R_MIPS_32
                // Handles 32-bit address relocation, used for things such as jump tables and pointers in data.

                // Check address is valid for relocation
                if ((*relocDataP & 0xF000000) == 0) {
                    *relocDataP = (*relocDataP - vRamStart) + allocu32;
                } else if (gLoadLogSeverity >= 3) {
                }
                break;

            case 0x4000000:
                // R_MIPS_26
                // Handles 26-bit address relocation, used for jumps and jals.

                *relocDataP =
                    (*relocDataP & 0xFC000000) |
                    (((allocu32 + ((((*relocDataP & 0x3FFFFFF) << 2) | 0x80000000) - vRamStart)) & 0xFFFFFFF) >> 2);
                break;

            case 0x5000000:
                // R_MIPS_HI16
                // Handles relocation for a hi/lo pair, part 1.
                // Store the reference to the LUI instruction, and update it in the R_MIPS_LO16 section.

                luiRefs[(*relocDataP >> 0x10) & 0x1F] = relocDataP;
                luiVals[(*relocDataP >> 0x10) & 0x1F] = *relocDataP;
                break;

            case 0x6000000:
                // R_MIPS_LO16
                // Handles relocation for a hi/lo pair, part 2.
                // Updates the LUI instruction (hi) to reflect the relocated address.
                // The full address is calculated from the LUI and lo parts, and then updated.
                // If the lo part is negative, add 1 to the LUI.

                luiInstRef = luiRefs[(*relocDataP >> 0x15) & 0x1F];
                regValP = &luiVals[((*relocDataP) >> 0x15) & 0x1F];

                // Check address is valid for relocation
                if ((((*luiInstRef << 0x10) + (s16)*relocDataP) & 0x0F000000) == 0) {
                    relocatedAddress = (*regValP << 0x10) + (s16)*relocDataP - vRamStart + allocu32;
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
    void* end;
    s32 pad;
    OverlayRelocationSection* ovl;

    if (gLoadLogSeverity >= 3) {}
    if (gLoadLogSeverity >= 3) {}

    end = (uintptr_t)allocatedVRamAddr + size;
    DmaMgr_SendRequest0(allocatedVRamAddr, vRomStart, size);

    ovl = (OverlayRelocationSection*)((uintptr_t)end - ((s32*)end)[-1]);

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
        bzero(end, ovl->bssSize);
    }

    osWritebackDCache(allocatedVRamAddr, allocatedBytes);
    osInvalICache(allocatedVRamAddr, allocatedBytes);

    if (gLoadLogSeverity >= 3) {}

    return allocatedBytes;
}

void* Load_AllocateAndLoad(uintptr_t vRomStart, uintptr_t vRomEnd, uintptr_t vRamStart) {
    size_t size = vRomEnd - vRomStart;
    void* end;
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

    ovlOffset = (uintptr_t)end - 4;
    ovl = (OverlayRelocationSection*)((uintptr_t)end - ((s32*)end)[-1]);

    if (1) {}

    allocatedBytes = ovl->bssSize + size;

    allocatedVRamAddr = SystemArena_Realloc(allocatedVRamAddr, allocatedBytes);

    if (gLoadLogSeverity >= 3) {}

    if (allocatedVRamAddr == NULL) {
        if (gLoadLogSeverity >= 3) {}
        return allocatedVRamAddr;
    }

    end = (uintptr_t)allocatedVRamAddr + size;
    ovl = (OverlayRelocationSection*)((uintptr_t)end - *(uintptr_t*)ovlOffset);

    if (gLoadLogSeverity >= 3) {}

    Load_Relocate(allocatedVRamAddr, ovl, vRamStart);

    if (ovl->bssSize != 0) {
        if (gLoadLogSeverity >= 3) {}
        bzero(end, ovl->bssSize);
    }

    osInvalICache(allocatedVRamAddr, allocatedBytes);

    if (gLoadLogSeverity >= 3) {}

    return allocatedVRamAddr;
}

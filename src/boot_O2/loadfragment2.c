#include "global.h"
#include "system_malloc.h"

s32 gLoad2LogSeverity = 2;

void Load2_Relocate(void* allocatedVRamAddr, OverlayRelocationSection* ovl, uintptr_t vRamStart) {
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

    if (gLoad2LogSeverity >= 3) {}

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
                } else if (gLoad2LogSeverity >= 3) {
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
                } else if (gLoad2LogSeverity >= 3) {
                }
                break;
        }
    }
}

size_t Load2_LoadOverlay(uintptr_t vRomStart, uintptr_t vRomEnd, uintptr_t vRamStart, uintptr_t vRamEnd,
                         void* allocatedVRamAddr) {
    s32 pad[2];
    size_t size = vRomEnd - vRomStart;
    void* end;
    OverlayRelocationSection* ovl;

    if (gLoad2LogSeverity >= 3) {}
    if (gLoad2LogSeverity >= 3) {}

    end = (uintptr_t)allocatedVRamAddr + size;
    DmaMgr_SendRequest0(allocatedVRamAddr, vRomStart, size);

    ovl = (OverlayRelocationSection*)((uintptr_t)end - ((s32*)end)[-1]);

    if (gLoad2LogSeverity >= 3) {}
    if (gLoad2LogSeverity >= 3) {}

    Load2_Relocate(allocatedVRamAddr, ovl, vRamStart);

    if (ovl->bssSize != 0) {
        if (gLoad2LogSeverity >= 3) {}
        bzero(end, ovl->bssSize);
    }

    size = vRamEnd - vRamStart;

    osWritebackDCache(allocatedVRamAddr, size);
    osInvalICache(allocatedVRamAddr, size);

    if (gLoad2LogSeverity >= 3) {}

    return size;
}

void* Load2_AllocateAndLoad(uintptr_t vRomStart, uintptr_t vRomEnd, uintptr_t vRamStart, uintptr_t vRamEnd) {
    void* allocatedVRamAddr = SystemArena_MallocR(vRamEnd - vRamStart);

    if (allocatedVRamAddr != NULL) {
        Load2_LoadOverlay(vRomStart, vRomEnd, vRamStart, vRamEnd, allocatedVRamAddr);
    }

    return allocatedVRamAddr;
}

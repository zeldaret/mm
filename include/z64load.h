#ifndef Z64LOAD_H
#define Z64LOAD_H

#include "ultra64/ultratypes.h"

#define RELOCATE_ADDR(addr, vRamStart, allocu32) ((addr) - (vRamStart) + (allocu32))

#define RELOC_SECTION(reloc) ((reloc) >> 30)
#define RELOC_OFFSET(reloc) ((reloc) & 0xFFFFFF)
#define RELOC_TYPE_MASK(reloc) ((reloc) & 0x3F000000)
#define RELOC_TYPE_SHIFT 24

/* MIPS Relocation Types */
#define R_MIPS_32 2
#define R_MIPS_26 4
#define R_MIPS_HI16 5
#define R_MIPS_LO16 6

typedef struct {
    /* 0x00 */ u32 textSize;
    /* 0x04 */ u32 dataSize;
    /* 0x08 */ u32 rodataSize;
    /* 0x0C */ u32 bssSize;
    /* 0x10 */ u32 nRelocations;
    /* 0x14 */ u32 relocations[1];
} OverlayRelocationSection; // size >= 0x18

size_t Load2_LoadOverlay(uintptr_t vRomStart, uintptr_t vRomEnd, uintptr_t vRamStart, uintptr_t vRamEnd, void* allocatedVRamAddr);
void* Load2_AllocateAndLoad(uintptr_t vRomStart, uintptr_t vRomEnd, uintptr_t vRamStart, uintptr_t vRamEnd);

#endif

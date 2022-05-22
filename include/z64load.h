#ifndef Z64LOAD_H
#define Z64LOAD_H

#include "PR/ultratypes.h"

#define RELOCATE_ADDR(addr, vRamStart, allocu32) ((addr) - (vRamStart) + (allocu32))

#define RELOC_SECTION(reloc) ((reloc) >> 0x1E)
#define RELOC_OFFSET(reloc) ((reloc) & 0xFFFFFF)
#define RELOC_TYPE(reloc) ((reloc) & 0x3F000000)

typedef enum MIPSRelocationType {
    R_MIPS_32 = 2,
    R_MIPS_26 = 4,
    R_MIPS_HI16 = 5,
    R_MIPS_LO16 = 6
} MIPSRelocationType;

typedef struct {
    /* 0x00 */ u32 textSize;
    /* 0x04 */ u32 dataSize;
    /* 0x08 */ u32 rodataSize;
    /* 0x0C */ u32 bssSize;
    /* 0x10 */ u32 nRelocations;
    /* 0x14 */ u32 relocations[1];
} OverlayRelocationSection; // size >= 0x18

#endif

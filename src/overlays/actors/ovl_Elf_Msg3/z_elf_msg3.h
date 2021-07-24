#ifndef Z_ELF_MSG3_H
#define Z_ELF_MSG3_H

#include "global.h"

struct ElfMsg3;

typedef struct ElfMsg3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ElfMsg3; // size = 0x148

extern const ActorInit Elf_Msg3_InitVars;

#endif // Z_ELF_MSG3_H

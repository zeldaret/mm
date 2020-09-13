#ifndef Z_ELF_MSG6_H
#define Z_ELF_MSG6_H

#include <global.h>

struct ElfMsg6;

typedef struct ElfMsg6 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ElfMsg6; // size = 0x148

extern const ActorInit Elf_Msg6_InitVars;

#endif // Z_ELF_MSG6_H

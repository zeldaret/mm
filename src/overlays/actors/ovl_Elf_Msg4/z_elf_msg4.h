#ifndef Z_ELF_MSG4_H
#define Z_ELF_MSG4_H

#include <global.h>

struct ElfMsg4;

typedef struct ElfMsg4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} ElfMsg4; // size = 0x14C

extern const ActorInit Elf_Msg4_InitVars;

#endif // Z_ELF_MSG4_H

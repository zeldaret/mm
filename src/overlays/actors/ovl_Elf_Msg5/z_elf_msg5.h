#ifndef _Z_ELF_MSG5_H_
#define _Z_ELF_MSG5_H_

#include <global.h>

struct ElfMsg5;

typedef struct ElfMsg5 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ElfMsg5; // size = 0x148

extern const ActorInit Elf_Msg5_InitVars;

#endif

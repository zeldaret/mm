#ifndef Z_ELF_MSG2_H
#define Z_ELF_MSG2_H

#include <global.h>

struct ElfMsg2;

typedef struct ElfMsg2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ElfMsg2; // size = 0x148

extern const ActorInit Elf_Msg2_InitVars;

#endif // Z_ELF_MSG2_H

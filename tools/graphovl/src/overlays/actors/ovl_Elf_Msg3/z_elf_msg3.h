#ifndef Z_ELF_MSG3_H
#define Z_ELF_MSG3_H

#include "global.h"

struct ElfMsg3;

typedef void (*ElfMsg3ActionFunc)(struct ElfMsg3*, GlobalContext*);

typedef struct ElfMsg3 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ElfMsg3ActionFunc actionFunc;
} ElfMsg3; // size = 0x148

extern const ActorInit Elf_Msg3_InitVars;

#endif // Z_ELF_MSG3_H

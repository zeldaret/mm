#ifndef Z_ELF_MSG5_H
#define Z_ELF_MSG5_H

#include "global.h"

struct ElfMsg5;

typedef void (*ElfMsg5ActionFunc)(struct ElfMsg5* this, GlobalContext* globalCtx);

typedef struct ElfMsg5 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ElfMsg5ActionFunc actionFunc;
} ElfMsg5; // size = 0x148

extern const ActorInit Elf_Msg5_InitVars;

#endif // Z_ELF_MSG5_H

#ifndef Z_ELF_MSG6_H
#define Z_ELF_MSG6_H

#include "global.h"

struct ElfMsg6;

typedef void (*ElfMsg6ActionFunc)(struct ElfMsg6* this, GlobalContext* globalCtx);

typedef struct ElfMsg6 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ElfMsg6ActionFunc actionFunc;
} ElfMsg6; // size = 0x148

extern const ActorInit Elf_Msg6_InitVars;

#endif // Z_ELF_MSG6_H

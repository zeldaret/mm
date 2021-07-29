#ifndef Z_ELF_MSG2_H
#define Z_ELF_MSG2_H

#include "global.h"

struct ElfMsg2;

typedef void (*ElfMsg2ActionFunc)(struct ElfMsg2* this, GlobalContext* globalCtx);

typedef struct ElfMsg2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ElfMsg2ActionFunc actionFunc;
} ElfMsg2; // size = 0x148

extern const ActorInit Elf_Msg2_InitVars;

#endif // Z_ELF_MSG2_H

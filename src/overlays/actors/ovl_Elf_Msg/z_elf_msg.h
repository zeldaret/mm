#ifndef Z_ELF_MSG_H
#define Z_ELF_MSG_H

#include "global.h"

struct ElfMsg;

typedef void (*ElfMsgActionFunc)(struct ElfMsg* this, GlobalContext* globalCtx);

typedef struct ElfMsg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ElfMsgActionFunc actionFunc;
} ElfMsg; // size = 0x148

extern const ActorInit Elf_Msg_InitVars;

#endif // Z_ELF_MSG_H

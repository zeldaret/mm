#ifndef Z_EN_ELF_H
#define Z_EN_ELF_H

#include "global.h"

struct EnElf;

typedef void (*EnElfActionFunc)(struct EnElf* this, GlobalContext* globalCtx);

typedef struct EnElf {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x120];
    /* 0x0264 */ u16 unk264;
    /* 0x0266 */ char unk_266[0xA];
    /* 0x0270 */ EnElfActionFunc actionFunc;
} EnElf; // size = 0x274

extern const ActorInit En_Elf_InitVars;

#endif // Z_EN_ELF_H

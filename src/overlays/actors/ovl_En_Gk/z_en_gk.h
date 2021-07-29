#ifndef Z_EN_GK_H
#define Z_EN_GK_H

#include "global.h"

struct EnGk;

typedef void (*EnGkActionFunc)(struct EnGk* this, GlobalContext* globalCtx);

typedef struct EnGk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnGkActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x180];
} EnGk; // size = 0x358

extern const ActorInit En_Gk_InitVars;

#endif // Z_EN_GK_H

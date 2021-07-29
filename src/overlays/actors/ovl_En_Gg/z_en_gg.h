#ifndef Z_EN_GG_H
#define Z_EN_GG_H

#include "global.h"

struct EnGg;

typedef void (*EnGgActionFunc)(struct EnGg* this, GlobalContext* globalCtx);

typedef struct EnGg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnGgActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x1B8];
} EnGg; // size = 0x390

extern const ActorInit En_Gg_InitVars;

#endif // Z_EN_GG_H

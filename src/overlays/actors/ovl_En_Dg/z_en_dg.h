#ifndef Z_EN_DG_H
#define Z_EN_DG_H

#include "global.h"

struct EnDg;

typedef void (*EnDgActionFunc)(struct EnDg* this, GlobalContext* globalCtx);

typedef struct EnDg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnDgActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x158];
} EnDg; // size = 0x2A0

extern const ActorInit En_Dg_InitVars;

#endif // Z_EN_DG_H

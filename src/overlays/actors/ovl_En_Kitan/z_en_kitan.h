#ifndef Z_EN_KITAN_H
#define Z_EN_KITAN_H

#include "global.h"

struct EnKitan;

typedef void (*EnKitanActionFunc)(struct EnKitan* this, GlobalContext* globalCtx);

typedef struct EnKitan {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x194];
    /* 0x02D8 */ EnKitanActionFunc actionFunc;
} EnKitan; // size = 0x2DC

extern const ActorInit En_Kitan_InitVars;

#endif // Z_EN_KITAN_H

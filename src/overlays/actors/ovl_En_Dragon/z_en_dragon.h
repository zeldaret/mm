#ifndef Z_EN_DRAGON_H
#define Z_EN_DRAGON_H

#include "global.h"

struct EnDragon;

typedef void (*EnDragonActionFunc)(struct EnDragon* this, GlobalContext* globalCtx);

typedef struct EnDragon {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x104];
    /* 0x0248 */ EnDragonActionFunc actionFunc;
    /* 0x024C */ char unk_24C[0x2B0];
} EnDragon; // size = 0x4FC

extern const ActorInit En_Dragon_InitVars;

#endif // Z_EN_DRAGON_H

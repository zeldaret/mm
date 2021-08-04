#ifndef Z_EN_BEE_H
#define Z_EN_BEE_H

#include "global.h"

struct EnBee;

typedef void (*EnBeeActionFunc)(struct EnBee* this, GlobalContext* globalCtx);

typedef struct EnBee {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xBC];
    /* 0x0200 */ EnBeeActionFunc actionFunc;
    /* 0x0204 */ char unk_204[0x84];
} EnBee; // size = 0x288

extern const ActorInit En_Bee_InitVars;

#endif // Z_EN_BEE_H

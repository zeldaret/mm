#ifndef Z_EN_BEE_H
#define Z_EN_BEE_H

#include "global.h"

struct EnBee;

typedef void (*EnBeeActionFunc)(struct EnBee*, PlayState*);

typedef struct EnBee {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xBC];
    /* 0x200 */ EnBeeActionFunc actionFunc;
    /* 0x204 */ char unk_204[0x84];
} EnBee; // size = 0x288

extern const ActorInit En_Bee_InitVars;

#endif // Z_EN_BEE_H

#ifndef Z_EN_BEE_H
#define Z_EN_BEE_H

#include "global.h"

struct EnBee;

typedef struct EnBee {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x144];
} EnBee; // size = 0x288

extern const ActorInit En_Bee_InitVars;

#endif // Z_EN_BEE_H

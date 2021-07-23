#ifndef Z_EN_WATER_EFFECT_H
#define Z_EN_WATER_EFFECT_H

#include "global.h"

struct EnWaterEffect;

typedef struct EnWaterEffect {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xCF8];
} EnWaterEffect; // size = 0xE3C

extern const ActorInit En_Water_Effect_InitVars;

#endif // Z_EN_WATER_EFFECT_H

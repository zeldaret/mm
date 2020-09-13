#ifndef Z_EN_OKARINA_EFFECT_H
#define Z_EN_OKARINA_EFFECT_H

#include <global.h>

struct EnOkarinaEffect;

typedef struct EnOkarinaEffect {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} EnOkarinaEffect; // size = 0x14C

extern const ActorInit En_Okarina_Effect_InitVars;

#endif // Z_EN_OKARINA_EFFECT_H

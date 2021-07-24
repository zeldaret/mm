#ifndef Z_DEMO_EFFECT_H
#define Z_DEMO_EFFECT_H

#include "global.h"

struct DemoEffect;

typedef struct DemoEffect {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x38];
} DemoEffect; // size = 0x17C

extern const ActorInit Demo_Effect_InitVars;

#endif // Z_DEMO_EFFECT_H

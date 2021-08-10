#ifndef Z_DEMO_EFFECT_H
#define Z_DEMO_EFFECT_H

#include "global.h"

struct DemoEffect;

typedef void (*DemoEffectActionFunc)(struct DemoEffect* this, GlobalContext* globalCtx);

typedef struct DemoEffect {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x34];
    /* 0x0178 */ DemoEffectActionFunc actionFunc;
} DemoEffect; // size = 0x17C

extern const ActorInit Demo_Effect_InitVars;

#endif // Z_DEMO_EFFECT_H

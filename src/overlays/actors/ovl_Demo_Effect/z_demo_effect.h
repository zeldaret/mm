#ifndef Z_DEMO_EFFECT_H
#define Z_DEMO_EFFECT_H

#include "global.h"
#include "z64curve.h"

struct DemoEffect;

typedef void (*DemoEffectActionFunc)(struct DemoEffect*, PlayState*);

#define DEMO_EFFECT_GET_TYPE(thisx) ((thisx)->params & 0xFF)

typedef enum {
    /* 0 */ DEMO_EFFECT_TYPE_0,
    /* 1 */ DEMO_EFFECT_TYPE_1,
    /* 2 */ DEMO_EFFECT_TYPE_2,
    /* 3 */ DEMO_EFFECT_TYPE_3,
    /* 4 */ DEMO_EFFECT_TYPE_4,
    /* 5 */ DEMO_EFFECT_TYPE_5,
    /* 6 */ DEMO_EFFECT_TYPE_6,
    /* 7 */ DEMO_EFFECT_TYPE_7,
    /* 8 */ DEMO_EFFECT_TYPE_8
} DemoEffectType;

typedef struct DemoEffect {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelCurve skelCurve;
    /* 0x164 */ u8 initObjectIndex;
    /* 0x165 */ u8 primXluColor[3];
    /* 0x168 */ u8 envXluColor[3];
    /* 0x16C */ s16 timer;
    /* 0x170 */ DemoEffectActionFunc initActionFunc;
    /* 0x174 */ ActorFunc initDrawFunc;
    /* 0x178 */ DemoEffectActionFunc actionFunc;
} DemoEffect; // size = 0x17C

extern const ActorInit Demo_Effect_InitVars;

#endif // Z_DEMO_EFFECT_H

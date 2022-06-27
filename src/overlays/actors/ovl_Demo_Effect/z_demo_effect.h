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
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelCurve skelCurve;
    /* 0x0164 */ u8 initObjectIndex;
    /* 0x0165 */ u8 primXluColor[3];
    /* 0x0168 */ u8 envXluColor[3];
    /* 0x016C */ s16 timer;
    /* 0x0170 */ DemoEffectActionFunc initActionFunc;
    /* 0x0174 */ ActorFunc initDrawFunc;
    /* 0x0178 */ DemoEffectActionFunc actionFunc;
} DemoEffect; // size = 0x17C

extern const ActorInit Demo_Effect_InitVars;

#endif // Z_DEMO_EFFECT_H

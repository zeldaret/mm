#ifndef Z_DEMO_EFFECT_H
#define Z_DEMO_EFFECT_H

#include "global.h"

struct DemoEffect;

typedef void (*DemoEffectActionFunc)(struct DemoEffect*, GlobalContext*);
typedef void (*DemoEffectUnkFunc)(struct DemoEffect*, GlobalContext*);
typedef void (*DemoEffectUnkFunc2)(Actor*, GlobalContext*);

#define DEMOEFFECT_GET_FF(thisx) ((thisx)->params & 0xFF)

typedef struct DemoEffect {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnimeCurve skelCurve;
    /* 0x0164 */ u8 unk_164;
    /* 0x0165 */ UNK_TYPE1 unk_165[3];
    /* 0x0168 */ u8 unk_168[3];
    /* 0x016C */ s16 unk_16C;
    /* 0x0170 */ DemoEffectUnkFunc unk_170;
    /* 0x0174 */ DemoEffectUnkFunc2 unk_174;
    /* 0x0178 */ DemoEffectActionFunc actionFunc;
} DemoEffect; // size = 0x17C

extern const ActorInit Demo_Effect_InitVars;

#endif // Z_DEMO_EFFECT_H

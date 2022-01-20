#ifndef Z_EN_TEST6_H
#define Z_EN_TEST6_H

#include "global.h"

struct EnTest6;

typedef void (*EnTest6ActionFunc)(struct EnTest6*, GlobalContext*);

typedef struct {
    /* 0x00 */ LightNode* node;
    /* 0x04 */ LightInfo info;
} EnTest6Light;

typedef struct EnTest6 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnTest6ActionFunc actionFunc;
    /* 0x0148 */ Gfx* unk_148;
    /* 0x014C */ f32 unk_14C;
    /* 0x0150 */ f32 unk_150;
    /* 0x0154 */ f32 unk_154;
    /* 0x0158 */ f32 unk_158;
    /* 0x015C */ f32 unk_15C;
    /* 0x0160 */ f32 unk_160;
    /* 0x0164 */ EnTest6Light lights[2];
    /* 0x018C */ DbCameraUnkStruct unk_18C;
    /* 0x020C */ Vec3f unk_20C[6];
    /* 0x0254 */ Vec3f (*unk_254)[64];
    /* 0x0258 */ Vec3f unk_258;
    /* 0x0264 */ Vec3f unk_264;
    /* 0x0270 */ f32 unk_270;
    /* 0x0274 */ s16 unk_274;
    /* 0x0276 */ s16 unk_276;
    /* 0x0278 */ s16 unk_278;
    /* 0x027A */ s16 unk_27A;
    /* 0x027C */ s16 unk_27C;
    /* 0x027E */ s16 unk_27E;
    /* 0x0280 */ s16 unk_280;
    /* 0x0282 */ s16 unk_282;
    /* 0x0284 */ s16 unk_284;
    /* 0x0286 */ s16 unk_286;
} EnTest6; // size = 0x288

extern const ActorInit En_Test6_InitVars;

#endif // Z_EN_TEST6_H

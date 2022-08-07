#ifndef Z_EN_TEST6_H
#define Z_EN_TEST6_H

#include "global.h"

struct EnTest6;

typedef void (*EnTest6ActionFunc)(struct EnTest6*, PlayState*);

#define ENTEST6_GET(thisx) ((thisx)->params)

enum {
    /* 24 */ ENTEST6_24 = 24,
    /* 25 */ ENTEST6_25,
    /* 26 */ ENTEST6_26,
};

typedef struct {
    /* 0x00 */ LightNode* node;
    /* 0x04 */ LightInfo info;
} EnTest6Light; // size = 0x14

typedef struct EnTest6 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnTest6ActionFunc actionFunc;
    /* 0x148 */ Gfx* unk_148;
    /* 0x14C */ f32 unk_14C;
    /* 0x150 */ f32 unk_150;
    /* 0x154 */ f32 unk_154;
    /* 0x158 */ f32 unk_158;
    /* 0x15C */ f32 unk_15C;
    /* 0x160 */ f32 unk_160;
    /* 0x164 */ EnTest6Light lights[2];
    /* 0x18C */ DbCameraUnkStruct unk_18C;
    /* 0x20C */ Vec3f unk_20C[6];
    /* 0x254 */ Vec3f (*unk_254)[64];
    /* 0x258 */ Vec3f subCamAt;
    /* 0x264 */ Vec3f subCamEye;
    /* 0x270 */ f32 subCamFov;
    /* 0x274 */ s16 unk_274;
    /* 0x276 */ s16 unk_276;
    /* 0x278 */ s16 unk_278;
    /* 0x27A */ s16 unk_27A;
    /* 0x27C */ s16 unk_27C;
    /* 0x27E */ s16 unk_27E;
    /* 0x280 */ s16 unk_280;
    /* 0x282 */ s16 unk_282;
    /* 0x284 */ s16 subCamId;
    /* 0x286 */ s16 unk_286;
} EnTest6; // size = 0x288

extern const ActorInit En_Test6_InitVars;

#endif // Z_EN_TEST6_H

#ifndef Z_EN_ARROW_H
#define Z_EN_ARROW_H

#include "global.h"

struct EnArrow;

typedef void (*EnArrowActionFunc)(struct EnArrow*, GlobalContext*);

enum {
    /* -8  */ ENARROW_MINUS8 = -8,
    /*  0  */ ENARROW_0 = 0,
    /*  1  */ ENARROW_1,
    /*  2  */ ENARROW_2,
    /*  3  */ ENARROW_3,
    /*  4  */ ENARROW_4,
    /*  5  */ ENARROW_5,
    /*  6  */ ENARROW_6,
    /*  7  */ ENARROW_7,
    /*  8  */ ENARROW_8,
};

typedef struct {
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[5];
} EnArrowArrow; // size = 0x1A8

typedef struct {
    /* 0x0144 */ f32 unk_144;
    /* 0x0148 */ u8 unk_148;
    /* 0x0149 */ s8 unk_149;
    /* 0x014A */ s16 unk_14A;
    /* 0x014C */ s16 unk_14C;
    /* 0x014E */ char unk_14E[0x5A];
} EnArrowBubble; // size = 0x1A8

typedef struct EnArrow {
    /* 0x0000 */ Actor actor;
    union {
        EnArrowArrow arrow;
        EnArrowBubble bubble;
    };
    /* 0x01A8 */ ColliderQuad collider;
    /* 0x0228 */ Vec3f unk_228;
    /* 0x0234 */ Vec3f unk_234;
    /* 0x0240 */ s32 unk_240;
    /* 0x0244 */ s32 unk_244;
    /* 0x0248 */ f32 unk_248;
    /* 0x024C */ f32 unk_24C;
    /* 0x0250 */ f32 unk_250;
    /* 0x0254 */ f32 unk_254;
    /* 0x0258 */ f32 unk_258;
    /* 0x025C */ f32 unk_25C;
    /* 0x0260 */ u8 unk_260; // timer in OoT
    /* 0x0261 */ u8 unk_261; // hitFlags in OoT
    /* 0x0262 */ u8 unk_262;
    /* 0x0263 */ u8 unk_263;
    /* 0x0264 */ Actor* unk_264;
    /* 0x0268 */ Vec3f unk_268;
    /* 0x0274 */ EnArrowActionFunc actionFunc;
} EnArrow; // size = 0x278

extern const ActorInit En_Arrow_InitVars;

#endif // Z_EN_ARROW_H

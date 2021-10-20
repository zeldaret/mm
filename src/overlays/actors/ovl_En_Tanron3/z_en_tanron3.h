#ifndef Z_EN_TANRON3_H
#define Z_EN_TANRON3_H

#include "global.h"

struct EnTanron3;

typedef void (*EnTanron3ActionFunc)(struct EnTanron3*, GlobalContext*);

typedef struct EnTanron3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[10];
    /* 0x1C4 */ Vec3s morphTable[10];
    /* 0x200 */ s16 unk_200;
    /* 0x202 */ char unk_202[0x2];
    /* 0x204 */ s16 unk_204;
    /* 0x206 */ char unk_206[0x16];
    /* 0x21C */ Vec3f unk_21C;
    /* 0x228 */ f32 unk_228;
    /* 0x22C */ f32 unk_22C;
    /* 0x230 */ f32 unk_230;
    /* 0x234 */ s16 unk_234;
    /* 0x236 */ char unk_236[0x2];
    /* 0x238 */ s16 unk_238;
    /* 0x23A */ char unk_23A[0x6];
    /* 0x240 */ f32 unk_240;
    /* 0x244 */ f32 unk_244;
    /* 0x248 */ char unk_248[0x8];
    /* 0x250 */ s32 unk_250;
    /* 0x254 */ char unk_254[0xC];
    /* 0x260 */ ColliderCylinder collider1;
    /* 0x2AC */ ColliderCylinder collider2;
    /* 0x2F8 */ EnTanron3ActionFunc actionFunc;
} EnTanron3; // size = 0x2FC

extern const ActorInit En_Tanron3_InitVars;

#endif // Z_EN_TANRON3_H

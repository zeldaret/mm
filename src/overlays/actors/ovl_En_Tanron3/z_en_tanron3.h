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
    /* 0x200 */ char unk_200[0x44];
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

#ifndef Z_EN_BAGUO_H
#define Z_EN_BAGUO_H

#include "global.h"

struct EnBaguo;

typedef void (*EnBaguoActionFunc)(struct EnBaguo*, GlobalContext*);

typedef struct EnBaguoUnkStruct {
    /* 0x00 */ u8 isVisible;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ char unk_10[0x18];
    /* 0x28 */ s16 xRotation;
    /* 0x2A */ s16 yRotation;
    /* 0x2C */ s16 zRotation;
    /* 0x30 */ f32 scale;
    /* 0x34 */ s16 timer;
} EnBaguoUnkStruct; // size = 0x38

typedef struct EnBaguo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[3];
    /* 0x019A */ Vec3s morphTable[3];
    /* 0x01AC */ EnBaguoActionFunc actionFunc;
    /* 0x01B0 */ s16 eyeIndex;
    /* 0x01B2 */ s16 blinkTimer;
    /* 0x01B4 */ s16 unk_1B4;
    /* 0x01B6 */ s16 unk_1B6;
    /* 0x01B8 */ s16 unk_1B8;
    /* 0x01BC */ f32 unk_1BC;
    /* 0x01C0 */ u8 unk_1C0;
    /* 0x01C4 */ Vec3f unk_1C4;
    /* 0x01D0 */ Vec3f unk_1D0;
    /* 0x01DC */ ColliderJntSph collider;
    /* 0x01FC */ ColliderJntSphElement colliderElements[1];
    /* 0x023C */ EnBaguoUnkStruct unkStructArray[30];
} EnBaguo; // size = 0x8CC

extern const ActorInit En_Baguo_InitVars;

#endif // Z_EN_BAGUO_H

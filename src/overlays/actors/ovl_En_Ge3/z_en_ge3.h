#ifndef Z_EN_GE3_H
#define Z_EN_GE3_H

#include "global.h"
#include "z64snap.h"

struct EnGe3;

typedef void (*EnGe3ActionFunc)(struct EnGe3*, PlayState*);

#define GERUDO_AVEIL_GET_PATH(thisx) (((thisx)->params & 0xFC00) >> 10)
#define GERUDO_AVEIL_GET_EXIT(thisx) (((thisx)->params & 0x1F0) >> 4)
#define GERUDO_AVEIL_GET_TYPE(thisx) ((thisx)->params & 1)

#define GERUDO_AVEIL_PATH_NONE 0x3F

typedef struct EnGe3 {
    /* 0x000 */ PictoActor picto;
    /* 0x148 */ ColliderCylinder collider;
    /* 0x194 */ SkelAnime skelAnime;
    /* 0x1D8 */ Vec3s jointTable[24];
    /* 0x268 */ Vec3s morphTable[24];
    /* 0x2F8 */ s16 eyeIndex;
    /* 0x2FA */ s16 blinkTimer;
    /* 0x2FC */ Path *unk2FC;
    /* 0x300 */ s32 unk300;
    /* 0x304 */ Vec3s unk304;
    /* 0x30A */ Vec3s unk30A;
    /* 0x310 */ s16 unk310;
    /* 0x312 */ s16 unk312;
    /* 0x314 */ s16 unk314;
    /* 0x316 */ s16 unk316;
    /* 0x318 */ s16 unk318;
    /* 0x31C */ EnGe3ActionFunc actionFunc;
} EnGe3; // size = 0x320

extern const ActorInit En_Ge3_InitVars;

#endif // Z_EN_GE3_H

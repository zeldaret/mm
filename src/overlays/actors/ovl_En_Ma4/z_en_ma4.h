#ifndef Z_EN_MA4_H
#define Z_EN_MA4_H

#include <global.h>
#include "overlays/actors/ovl_En_Ma_Yts/z_en_ma_yts.h"

struct EnMa4;

typedef void (*EnMa4ActionFunc)(struct EnMa4*, GlobalContext*);

typedef struct EnMa4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnMa4ActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ struct_800BD888_arg1 unk_1D8;
    /* 0x200 */ Vec3s* unk_200;
    /* 0x204 */ Vec3s limbDrawTable[MA1_LIMB_MAX];
    /* 0x28E */ char unk28E[0x6];
    /* 0x294 */ Vec3s transitionDrawTable[MA1_LIMB_MAX];
    /* 0x31E */ char unk31E[0x6];
    /* 0x324 */ s16 unk_324;
    /* 0x326 */ s16 unk_326; // pathPointsCount
    /* 0x328 */ char unk_328[0x2]; // unused
    /* 0x32A */ s16 unk_32A; // blinkTimer
    /* 0x33C */ s16 unk_32C; // overrideEyeTexIndex
    /* 0x32E */ s16 unk_32E; // eyeTexIndex
    /* 0x330 */ s16 unk_330; // mouthTexIndex
    /* 0x332 */ s16 unk_332; // type?
    /* 0x334 */ u16 unk_334;
    /* 0x336 */ s16 unk_336;
    /* 0x338 */ s16 unk_338; // modified by EnPoFusen
    /* 0x33A */ s16 unk_33A;
    /* 0x33C */ s16 unk_33C;
    /* 0x33E */ u16 unk_33E;
} EnMa4; // size = 0x340

extern const ActorInit En_Ma4_InitVars;

#endif // Z_EN_MA4_H

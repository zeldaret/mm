#ifndef Z_EN_FISH2_H
#define Z_EN_FISH2_H

#include "global.h"

struct EnFish2;

typedef void (*EnFish2ActionFunc)(struct EnFish2*, PlayState*);

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ s16 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s16 unk_1C;
    /* 0x20 */ void* unk_20;
} EnFish2UnkStruct; // size = 0x24

typedef struct EnFish2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[24];
    /* 0x0218 */ Vec3s morphTable[24];
    /* 0x02A8 */ EnFish2ActionFunc actionFunc;
    /* 0x02AC */ s32 unk_2AC;
    /* 0x02B0 */ s32 unk_2B0;
    /* 0x02B4 */ s16 unk_2B4;
    /* 0x02B6 */ s16 unk_2B6;
    /* 0x02B8 */ s16 unk_2B8;
    /* 0x02BA */ s16 unk_2BA[3];
    /* 0x02C0 */ s32 unk_2C0;
    /* 0x02C4 */ s32 unk_2C4;
    /* 0x02C8 */ u8 unk_2C8;
    /* 0x02CA */ s16 subCamId;
    /* 0x02CC */ f32 unk_2CC;
    /* 0x02D0 */ char unk_2D0[0x4];
    /* 0x02D4 */ f32 unk_2D4;
    /* 0x02D8 */ f32 unk_2D8;
    /* 0x02DC */ Vec3f subCamEye;
    /* 0x02E8 */ Vec3f subCamAt;
    /* 0x02F4 */ Vec3f unk_2F4;
    /* 0x0300 */ Vec3f unk_300;
    /* 0x030C */ Vec3f unk_30C;
    /* 0x0318 */ Vec3f unk_318;
    /* 0x0324 */ Vec3f unk_324;
    /* 0x0330 */ f32 unk_330;
    /* 0x0334 */ f32 unk_334;
    /* 0x0338 */ f32 unk_338;
    /* 0x033C */ f32 unk_33C;
    /* 0x0340 */ s32 unk_340;
    /* 0x0344 */ s32 unk_344;
    /* 0x0348 */ s16 unk_348;
    /* 0x034A */ s16 unk_34A;
    /* 0x034C */ s16 unk_34C;
    /* 0x034E */ char unk_34E[0x02];
    /* 0x0350 */ Actor* unk_350;
    /* 0x0354 */ struct EnFish2* unk_354;
    /* 0x0358 */ ColliderJntSph collider;
    /* 0x0378 */ ColliderJntSphElement colliderElements[2];
    /* 0x03F8 */ EnFish2UnkStruct unk_3F8[200];
} EnFish2; // size = 0x2018

extern const ActorInit En_Fish2_InitVars;

#endif // Z_EN_FISH2_H

#ifndef Z_EN_RG_H
#define Z_EN_RG_H

#include "global.h"

struct EnRg;

typedef void (*EnRgActionFunc)(struct EnRg*, GlobalContext*);

#define ENRG_GET_7F80(thisx) ((((thisx)->params & 0x7F80) >> 7) & 0xFF)

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x03 */ UNK_TYPE1 unk_03[0xD];
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ Vec3f unk_28;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
} EnRgStruct; // size = 0x3C

typedef struct EnRg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnRgActionFunc actionFunc;
    /* 0x018C */ Actor* unk_18C;
    /* 0x0190 */ ColliderCylinder collider1;
    /* 0x01DC */ ColliderSphere collider2;
    /* 0x0234 */ Path* path;
    /* 0x0238 */ Vec3s jointTable[18];
    /* 0x02A4 */ Vec3s morphTable[18];
    /* 0x0310 */ u16 unk_310;
    /* 0x0314 */ f32 unk_314;
    /* 0x0318 */ s16 unk_318;
    /* 0x031A */ UNK_TYPE1 unk31A[2];
    /* 0x031C */ s16 unk_31C;
    /* 0x031E */ s16 unk_31E;
    /* 0x0320 */ s16 unk_320;
    /* 0x0322 */ s16 unk_322;
    /* 0x0324 */ s16 unk_324;
    /* 0x0326 */ s16 unk_326;
    /* 0x0328 */ s16 unk_328[3];
    /* 0x032E */ s16 unk_32E[3];
    /* 0x0334 */ s32 unk_334;
    /* 0x0338 */ UNK_TYPE1 unk338[4];
    /* 0x033C */ s32 unk_33C;
    /* 0x0340 */ s32 unk_340;
    /* 0x0344 */ s32 unk_344;
    /* 0x0348 */ s32 numCheckpointsAheadOfPlayer;
    /* 0x034C */ EnRgStruct unk_34C[32];
} EnRg; // size = 0xACC

extern const ActorInit En_Rg_InitVars;

#endif // Z_EN_RG_H

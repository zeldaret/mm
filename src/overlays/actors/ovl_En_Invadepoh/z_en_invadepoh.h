#ifndef Z_EN_INVADEPOH_H
#define Z_EN_INVADEPOH_H

#include "global.h"

struct EnInvadepoh;

typedef void (*EnInvadepohActionFunc)(struct EnInvadepoh* this, PlayState* play);

typedef struct {
    f32 unk0;
    s16 unk4;
    s16 unk6;
} EnInvadepohUnkStruct1;

typedef struct {
    s8* unk0;
    s8 unk4;
} EnInvadepohUnkStruct2;

typedef struct {
    s8 unk0;
    EnInvadepohUnkStruct2* unk4;
} EnInvadepohUnkStruct3;

typedef struct {
    s8 unk0;
    f32 unk4;
} EnInvadepohUnkStruct4;

typedef struct {
    s8 unk0;
    EnInvadepohUnkStruct2* unk4;
    s8 unk8;
    EnInvadepohUnkStruct4* unkC;
} EnInvadepohUnkStruct5;

typedef struct {
    s8 unk0;
    EnInvadepohUnkStruct2* unk4;
    s8 unk8;
    EnInvadepohUnkStruct4* unkC;
    s16 unk10;
    s16 unk12;
} EnInvadepohUnkStruct6;

typedef union {
    EnInvadepohUnkStruct3 unk3;
    EnInvadepohUnkStruct5 unk5;
    EnInvadepohUnkStruct6 unk6;
} EnInvadepohUnkUnion;

typedef struct {
    s8 unk_0;
    s8 unk_1;
    u8 unk_2;
    Vec3f unk_4;
} EnInvadepohStructD_80B50350;

typedef struct {
    EnInvadepohUnkUnion** unk_0;
    s8 unk_4;
    EnInvadepohUnkUnion* unk_8;
    s16 unk_C;
    s8 unk_E;
    s8 unk_F;
} EnInvadePohUnkStruct_324_1;

typedef struct {
    EnInvadePohUnkStruct_324_1 unk_00;
    EnInvadePohUnkStruct_324_1 unk_10;
    Vec3s unk_20;
    Vec3s unk_26;
    s16 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C;
    s16 unk_40;
    s16 unk_42;
    f32 unk_44;
    s16 unk_48;
} EnInvadePohUnkStruct_324;

typedef void (*EnInvadepohUnkFunc) (EnInvadePohUnkStruct_324_1*, EnInvadepohUnkUnion**);

typedef struct EnInvadepoh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s unk_188[23];
    /* 0x212 */ Vec3s unk_212[23];
    /* 0x29C */ s8 unk_29C;
    /* 0x2A0 */ ColliderCylinder unk_2A0;
    /* 0x2EC */ EnInvadepohActionFunc actionFunc;
    /* 0x2F0 */ s16 unk_2F0;
    /* 0x2F2 */ s16 unk_2F2;
    /* 0x2F4 */ s8 unk_2F4;
    /* 0x2F8 */ f32 unk_2F8;
    /* 0x2FC */ char unk_2FC[4]; // unused? f32?
    /* 0x300 */ f32 unk_300;
    /* 0x304 */ s16 unk_304;
    /* 0x306 */ s16 unk_306;
    /* 0x308 */ s8 unk_308;
    /* 0x309 */ s8 unk_309;
    /* 0x30A */ s8 unk_30A;
    /* 0x30C */ Vec3s *unk_30C;
    /* 0x310 */ f32 unk_310;
    /* 0x314 */ Vec3f unk_314;
    /* 0x320 */ f32 unk_320;
    /* 0x324 */ EnInvadePohUnkStruct_324 unk_324;
    /* 0x370 */ s16 unk_370;
    /* 0x372 */ s16 unk_372;
    /* 0x374 */ s8 unk_374;
    /* 0x376 */ u16 unk_376;
    /* 0x378 */ s8 unk_378;
    /* 0x379 */ s8 unk_379;
    /* 0x37C */ f32 unk_37C[3];
    /* 0x388 */ char unk_388; // unused?
    /* 0x389 */ u8 unk_389;
    /* 0x38A */ s8 unk_38A;
    /* 0x38B */ s8 unk_38B;
    /* 0x38C */ s8 unk_38C;
    /* 0x38D */ u8 unk_38D;
    /* 0x390 */ Vec3f unk_390;
    /* 0x39C */ f32 unk_39C;
    /* 0x3A0 */ f32 unk_3A0;
    /* 0x3A4 */ f32 unk_3A4;
    /* 0x3A8 */ s16 unk_3A8;
    /* 0x3AA */ s16 unk_3AA;
    /* 0x3AC */ s8 unk_3AC;
    /* 0x3AD */ char pad3AD[3];
    /* 0x3B0 */ char pad3B0[0xC]; // unused? Vec3f?
    /* 0x3BC */ s8 unk_3BC;
} EnInvadepoh; // size = 0x3C0

extern ActorInit En_Invadepoh_InitVars;

#endif // Z_EN_INVADEPOH_H

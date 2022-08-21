#ifndef Z_EN_WIZ_H
#define Z_EN_WIZ_H

#include "global.h"

struct EnWiz;

typedef void (*EnWizActionFunc)(struct EnWiz*, PlayState*);

typedef struct EnWiz {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[20];
    /* 0x200 */ Vec3s morphTable[20];
    /* 0x278 */ SkelAnime skelAnime2;
    /* 0x2BC */ Vec3s jointTable2[20];
    /* 0x334 */ Vec3s morphTable2[20];
    /* 0x3AC */ EnWizActionFunc actionFunc;
    /* 0x3B0 */ s16 unk_3B0;
    /* 0x3B2 */ s16 unk_3B2;
    /* 0x3B4 */ s16 unk_3B4;
    /* 0x3B6 */ s16 unk_3B6;
    /* 0x3B8 */ s16 unk_388;
    /* 0x3BA */ s16 unk_3BA;
    /* 0x3BC */ s16 unk_3BC;
    /* 0x3B4 */ char unk_3BE[4];
    /* 0x3C2 */ s16 unk_3C2;
    /* 0x3C4 */ s16 unk_3C4;
    /* 0x3C6 */ s16 unk_3C6;
    /* 0x3C8 */ char unk_3C8[2];
    /* 0x3CA */ s8 unk_3CA;
    /* 0x3CB */ u8 unk_3CB;
    /* 0x3CC */ char unk_3CC[4];
    /* 0x3D0 */ f32 endFrame;
    /* 0x3D4 */ f32 unk_3D4;
    /* 0x3D8 */ char unk_3D8[0x18];
    /* 0x3F0 */ Vec3f unk_3F0;
    /* 0x3FC */ char unk_3FC[0x18];
    /* 0x414 */ Vec3f unk_414;
    /* 0x420 */ char unk_420[0x28];
    /* 0x448 */ s32 unk_448;
    /* 0x44C */ char unk_44C[4];
    /* 0x450 */ f32 unk_450;
    /* 0x454 */ ColliderJntSph unk_454;
    /* 0x474 */ ColliderJntSphElement unk_474[10];
    /* 0x6F4 */ ColliderCylinder unk_6F4;
    /* 0x740 */ s32 unk_740;
    /* 0x744 */ s32 unk_744;
    /* 0x748 */ s16 unk_748;
    /* 0x74A */ s16 unk_74A;
    /* 0x74C */ s16 switchFlag;
    /* 0x74E */ s16 unk_74E;
    /* 0x750 */ char unk_750[0xCC];
    /* 0x81C */ Vec3f unk_81C[10];
    /* 0x894 */ Vec3s unk_894[10];
    /* 0x8D0 */ char unk_898[0x4B0];
} EnWiz; // size = 0xD80

extern const ActorInit En_Wiz_InitVars;

#endif // Z_EN_WIZ_H

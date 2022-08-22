#ifndef Z_EN_WIZ_H
#define Z_EN_WIZ_H

#include "global.h"
#include "objects/object_wiz/object_wiz.h"

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
    /* 0x3B4 */ char unk_3BE[2];
    /* 0x3C0 */ s16 unk_3C0;
    /* 0x3C2 */ s16 unk_3C2;
    /* 0x3C4 */ s16 unk_3C4;
    /* 0x3C6 */ s16 unk_3C6;
    /* 0x3C8 */ s16 unk_3C8;
    /* 0x3CA */ u8 unk_3CA;
    /* 0x3CB */ u8 unk_3CB;
    /* 0x3CC */ s32 unk_3CC;
    /* 0x3D0 */ f32 endFrame;
    /* 0x3D4 */ f32 unk_3D4;
    /* 0x3D8 */ Vec3f unk_3D8;
    /* 0x3E4 */ f32 unk_3E4;
    /* 0x3E8 */ f32 unk_3E8;
    /* 0x3EC */ f32 unk_3EC;
    /* 0x3F0 */ Vec3f unk_3F0;
    /* 0x3FC */ char unk_3FC[0x18];
    /* 0x414 */ Vec3f unk_414;
    /* 0x420 */ Actor* unk_420[10];
    /* 0x448 */ s32 unk_448;
    /* 0x44C */ s16 unk_44C;
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
    /* 0x750 */ s16 unk_750;
    /* 0x752 */ s16 drawDmgEffTimer;
    /* 0x754 */ s16 drawDmgEffType;
    /* 0x758 */ f32 drawDmgEffScale;
    /* 0x75C */ f32 drawDmgEffFrozenSteamScale;
    /* 0x760 */ Vec3f bodyPartsPos[12];
    /* 0x7F0 */ s16 bodyPartsPosIndex;
    /* 0x7F2 */ s16 unk_7F2[10];
    /* 0x806 */ s16 unk_806[10];
    /* 0x81C */ Vec3f unk_81C[10];
    /* 0x894 */ Vec3s unk_894[10];
    /* 0x8D0 */ Vec3s jointTable3[10][20];
} EnWiz; // size = 0xD80

extern const ActorInit En_Wiz_InitVars;

#endif // Z_EN_WIZ_H

#ifndef Z_EN_JG_H
#define Z_EN_JG_H

#include "global.h"

struct EnJg;

typedef void (*EnJgActionFunc)(struct EnJg*, GlobalContext*);

typedef struct EnJg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Actor* unk_144;
    /* 0x148 */ Actor* unk_148;
    /* 0x14C */ ColliderCylinder collider;
    /* 0x198 */ SkelAnime skelAnime;
    /* 0x1DC */ EnJgActionFunc actionFunc;
    /* 0x1E0 */ Path* unk_1E0;
    /* 0x1E4 */ s32 unk_1E4;
    /* 0x1E8 */ Actor* unk_1E8;
    /* 0x1EC */ Vec3s unk_1EC;
    /* 0x1F2 */ Vec3s unk_1F2;
    /* 0x1F8 */ Vec3s jointTable[35];
    /* 0x2CA */ Vec3s morphTable[35];
    /* 0x39C */ s16 unk_39C;
    /* 0x39E */ s16 unk_39E;
    /* 0x3A0 */ s16 unk_3A0;
    /* 0x3A2 */ s16 unk_3A2;
    /* 0x3A4 */ Vec3f unk_3A4;
    /* 0x3B0 */ Vec3f unk_3B0;
    /* 0x3BC */ Vec3f unk_3BC;
    /* 0x3C8 */ s16 unk_3C8;
    /* 0x3CA */ u8 unk_3CA;
    /* 0x3CB */ u8 unk_3CB;
    /* 0x3CC */ u16 unk_3CC;
    /* 0x3CE */ u16 unk_3CE;
    /* 0x3D0 */ u8 unk_3D0;
    /* 0x3D1 */ char unk_3D1[0x3];
} EnJg; // size = 0x3D4

extern const ActorInit En_Jg_InitVars;

#endif // Z_EN_JG_H

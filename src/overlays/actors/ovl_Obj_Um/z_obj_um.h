#ifndef Z_OBJ_UM_H
#define Z_OBJ_UM_H

#include "global.h"

struct ObjUm;

typedef void (*ObjUmActionFunc)(struct ObjUm*, GlobalContext*);

typedef struct ObjUm {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjUmActionFunc actionFunc;
    /* 0x160 */ SkelAnime unk_160;
    /* 0x1A4 */ Vec3s unk_1A4[0x16];
    /* 0x228 */ Vec3s unk_228[0x16];

    /* 0x2AC */ s16 unk_2AC;
    /* 0x2AE */ s16 unk_2AE;
    /* 0x2B0 */ s16 unk_2B0;

    /* 0x2B2 */ char unk_2B2[0x2]; // padding probably
    /* 0x2B4 */ UNK_TYPE unk_2B4;

    /* 0x2B8 */ Actor* unk_2B8;

    /* 0x2BC */ s32 unk_2BC;
    /* 0x2BE */ char unk_2BE[0x4]; // Vec3s* ?

    /* 0x2C4 */ Vec3f unk_2C4;

    /* 0x2D0 */ char unk_2D0[0xC];

    /* 0x2DC */ Vec3f unk_2DC;

    /* 0x2E8 */ char unk_2E8[0x8];

    /* 0x2F0 */ char unk_2F0[0x4];
    /* 0x2F4 */ s32 unk_2F4;

    /* 0x2BC */ Vec3s unk_2F8;
    /* 0x2FE */ Vec3s unk_2FE;

    /* 0x304 */ s32 unk_304;
    /* 0x308 */ Vec3f unk_308;

    /* 0x314 */ UNK_TYPE unk_314[3];
    /* 0x320 */ UNK_TYPE unk_320[3];

    /* 0x32C */ Vec3f unk_32C[3];

    /* 0x350 */ UNK_TYPE unk_350;
    /* 0x354 */ UNK_TYPE unk_354;

    /* 0x358 */ Actor* unk_358;
    /* 0x35C */ Actor* unk_35C;
    /* 0x360 */ char unk_360[0xC0];

    /* 0x420 */ UNK_TYPE unk_420;

    /* 0x424 */ ColliderCylinder unk_424;
    /* 0x470 */ ColliderCylinder unk_470;
    /* 0x4BC */ Vec3f unk_4BC;
    /* 0x4C8 */ u16 unk_4C8;
    /* 0x4CA */ char unk_4CA[0x2]; // padding probably

    /* 0x4CC */ UNK_TYPE unk_4CC;
    /* 0x4D0 */ UNK_TYPE unk_4D0;
    /* 0x4D4 */ UNK_TYPE unk_4D4;
    /* 0x4D8 */ char unk_4D8[0x4];
    /* 0x4DC */ UNK_TYPE unk_4DC;
    /* 0x4E0 */ UNK_TYPE unk_4E0;
} ObjUm; // size = 0x4E4

extern const ActorInit Obj_Um_InitVars;

#endif // Z_OBJ_UM_H

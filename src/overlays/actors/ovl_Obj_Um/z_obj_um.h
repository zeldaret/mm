#ifndef Z_OBJ_UM_H
#define Z_OBJ_UM_H

#include "global.h"

struct ObjUm;

typedef void (*ObjUmActionFunc)(struct ObjUm*, GlobalContext*);

typedef struct ObjUm {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjUmActionFunc unk_15C;
    /* 0x160 */ SkelAnime unk_160;
    /* 0x1A4 */ Vec3s unk_1A4[0x16];
    /* 0x228 */ Vec3s unk_228[0x16];
    /* 0x2AC */ char unk_2AC[0xC];
    /* 0x2B8 */ Actor* unk_2B8;
    /* 0x2BC */ char unk_2BC[0x38];
    /* 0x2F4 */ s32 unk_2F4;
    /* 0x2BC */ char unk_2F8[0xC];
    /* 0x304 */ s32 unk_304;
    /* 0x308 */ char unk_308[0x24];
    /* 0x32C */ Vec3f unk_32C[3];
    /* 0x350 */ char unk_350[0xD4];
    /* 0x424 */ ColliderCylinder unk_424;
    /* 0x470 */ ColliderCylinder unk_470;
    /* 0x4BC */ Vec3f unk_4BC;
    /* 0x4C8 */ char unk_4C8[0x1C];
} ObjUm; // size = 0x4E4

extern const ActorInit Obj_Um_InitVars;

#endif // Z_OBJ_UM_H

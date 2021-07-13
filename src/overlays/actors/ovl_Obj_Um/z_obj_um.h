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
    /* 0x2AC */ char unk_2AC[0x58];
    /* 0x304 */ s32 unk_304;
    /* 0x308 */ char unk_308[0x11C];
    /* 0x424 */ ColliderCylinder unk_424;
    /* 0x470 */ ColliderCylinder unk_470;
    /* 0x4BC */ char unk_4BC[0x28];
} ObjUm; // size = 0x4E4

extern const ActorInit Obj_Um_InitVars;

#endif // Z_OBJ_UM_H

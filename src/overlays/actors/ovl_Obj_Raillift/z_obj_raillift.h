#ifndef Z_OBJ_RAILLIFT_H
#define Z_OBJ_RAILLIFT_H

#include <global.h>

struct ObjRaillift;

typedef void (*ObjRailliftActionFunc)(struct ObjRaillift*, GlobalContext*);

typedef struct ObjRaillift {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjRailliftActionFunc actionFunc;
    /* 0x160 */ f32 unk160;
    /* 0x164 */ s32 unk164;
    /* 0x168 */ s32 unk168;
    /* 0x16C */ s32 unk16C;
    /* 0x170 */ Vec3s* unk170;
    /* 0x174 */ s32 unk174;
    /* 0x178 */ s32 unk178;
    /* 0x17C */ f32 unk17C;
    /* 0x180 */ f32 unk180;
    /* 0x184 */ s16 unk184;
    /* 0x186 */ s16 unk186;
    /* 0x188 */ s16 unk188;
    /* 0x18A */ char unk18A[0x2];
} ObjRaillift; // size = 0x18C

extern const ActorInit Obj_Raillift_InitVars;

#endif // Z_OBJ_RAILLIFT_H

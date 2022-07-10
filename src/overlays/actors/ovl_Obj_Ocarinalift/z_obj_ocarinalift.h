#ifndef Z_OBJ_OCARINALIFT_H
#define Z_OBJ_OCARINALIFT_H

#include "global.h"

struct ObjOcarinalift;

typedef void (*ObjOcarinaliftActionFunc)(struct ObjOcarinalift*, PlayState*);

typedef struct ObjOcarinalift {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ObjOcarinaliftActionFunc actionFunc;
    /* 0x160 */ f32 unk160;
    /* 0x164 */ s32 unk164;
    /* 0x168 */ s32 unk168;
    /* 0x16C */ s32 unk16C;
    /* 0x170 */ Vec3s* unk170; // pointer segun mips2c
    /* 0x174 */ s16 unk174;
    /* 0x176 */ s16 unk176;
} ObjOcarinalift; // size = 0x178

extern const ActorInit Obj_Ocarinalift_InitVars;

#endif // Z_OBJ_OCARINALIFT_H

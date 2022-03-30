#ifndef Z_OBJ_BIGICICLE_H
#define Z_OBJ_BIGICICLE_H

#include "global.h"

struct ObjBigicicle;

typedef void (*ObjBigicicleActionFunc)(struct ObjBigicicle*, GlobalContext*);

#define OBJBIGICLE_GET_FF00(thisx) (((thisx)->params >> 8) & 0xFF)

typedef struct ObjBigicicle {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjBigicicleActionFunc actionFunc;
    /* 0x0148 */ u8 unk_148;
    /* 0x0149 */ u8 unk_149;
    /* 0x014A */ s16 unk_14A;
    /* 0x014C */ ColliderCylinder collider1;
    /* 0x0198 */ ColliderCylinder collider2;
} ObjBigicicle; // size = 0x1E4

extern const ActorInit Obj_Bigicicle_InitVars;

#endif // Z_OBJ_BIGICICLE_H

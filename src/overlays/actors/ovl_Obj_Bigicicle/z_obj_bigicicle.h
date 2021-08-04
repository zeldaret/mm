#ifndef Z_OBJ_BIGICICLE_H
#define Z_OBJ_BIGICICLE_H

#include "global.h"

struct ObjBigicicle;

typedef void (*ObjBigicicleActionFunc)(struct ObjBigicicle* this, GlobalContext* globalCtx);

typedef struct ObjBigicicle {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjBigicicleActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x9C];
} ObjBigicicle; // size = 0x1E4

extern const ActorInit Obj_Bigicicle_InitVars;

#endif // Z_OBJ_BIGICICLE_H

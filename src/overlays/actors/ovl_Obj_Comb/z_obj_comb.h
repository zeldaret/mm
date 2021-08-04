#ifndef Z_OBJ_COMB_H
#define Z_OBJ_COMB_H

#include "global.h"

struct ObjComb;

typedef void (*ObjCombActionFunc)(struct ObjComb* this, GlobalContext* globalCtx);

typedef struct ObjComb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjCombActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x74];
} ObjComb; // size = 0x1BC

extern const ActorInit Obj_Comb_InitVars;

#endif // Z_OBJ_COMB_H

#ifndef Z_OBJ_HUGEBOMBIWA_H
#define Z_OBJ_HUGEBOMBIWA_H

#include "global.h"

struct ObjHugebombiwa;

typedef void (*ObjHugebombiwaActionFunc)(struct ObjHugebombiwa* this, GlobalContext* globalCtx);

typedef struct ObjHugebombiwa {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x370];
    /* 0x04B4 */ ObjHugebombiwaActionFunc actionFunc;
} ObjHugebombiwa; // size = 0x4B8

extern const ActorInit Obj_Hugebombiwa_InitVars;

#endif // Z_OBJ_HUGEBOMBIWA_H

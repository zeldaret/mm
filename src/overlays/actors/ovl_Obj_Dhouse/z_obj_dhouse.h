#ifndef Z_OBJ_DHOUSE_H
#define Z_OBJ_DHOUSE_H

#include "global.h"

struct ObjDhouse;

typedef void (*ObjDhouseActionFunc)(struct ObjDhouse* this, GlobalContext* globalCtx);

typedef struct ObjDhouse {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjDhouseActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x1214];
} ObjDhouse; // size = 0x1374

extern const ActorInit Obj_Dhouse_InitVars;

#endif // Z_OBJ_DHOUSE_H

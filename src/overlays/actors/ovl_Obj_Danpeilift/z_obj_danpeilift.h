#ifndef Z_OBJ_DANPEILIFT_H
#define Z_OBJ_DANPEILIFT_H

#include "global.h"

struct ObjDanpeilift;

typedef void (*ObjDanpeiliftActionFunc)(struct ObjDanpeilift* this, GlobalContext* globalCtx);

typedef struct ObjDanpeilift {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjDanpeiliftActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x2C];
} ObjDanpeilift; // size = 0x18C

extern const ActorInit Obj_Danpeilift_InitVars;

#endif // Z_OBJ_DANPEILIFT_H

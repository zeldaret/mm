#ifndef Z_OBJ_DANPEILIFT_H
#define Z_OBJ_DANPEILIFT_H

#include "global.h"

struct ObjDanpeilift;

typedef void (*ObjDanpeiliftActionFunc)(struct ObjDanpeilift*, PlayState*);

typedef struct ObjDanpeilift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
    /* 0x15C */ ObjDanpeiliftActionFunc actionFunc;
    /* 0x160 */ char unk_160[0x2C];
} ObjDanpeilift; // size = 0x18C

extern const ActorInit Obj_Danpeilift_InitVars;

#endif // Z_OBJ_DANPEILIFT_H

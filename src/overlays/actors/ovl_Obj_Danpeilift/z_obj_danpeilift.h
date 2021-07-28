#ifndef Z_OBJ_DANPEILIFT_H
#define Z_OBJ_DANPEILIFT_H

#include "global.h"

struct ObjDanpeilift;

typedef struct ObjDanpeilift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x48];
} ObjDanpeilift; // size = 0x18C

extern const ActorInit Obj_Danpeilift_InitVars;

#endif // Z_OBJ_DANPEILIFT_H

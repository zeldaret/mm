#ifndef _Z_OBJ_DANPEILIFT_H_
#define _Z_OBJ_DANPEILIFT_H_

#include <global.h>

struct ObjDanpeilift;

typedef struct ObjDanpeilift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x48];
} ObjDanpeilift; // size = 0x18C

extern const ActorInit Obj_Danpeilift_InitVars;

#endif

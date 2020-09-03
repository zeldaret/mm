#ifndef _Z_OBJ_RAILLIFT_H_
#define _Z_OBJ_RAILLIFT_H_

#include <global.h>

struct ObjRaillift;

typedef struct ObjRaillift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x48];
} ObjRaillift; // size = 0x18C

extern const ActorInit Obj_Raillift_InitVars;

#endif

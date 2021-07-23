#ifndef Z_OBJ_LUPYGAMELIFT_H
#define Z_OBJ_LUPYGAMELIFT_H

#include "global.h"

struct ObjLupygamelift;

typedef struct ObjLupygamelift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x30];
} ObjLupygamelift; // size = 0x174

extern const ActorInit Obj_Lupygamelift_InitVars;

#endif // Z_OBJ_LUPYGAMELIFT_H

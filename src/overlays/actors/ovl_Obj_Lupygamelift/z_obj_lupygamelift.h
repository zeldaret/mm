#ifndef _Z_OBJ_LUPYGAMELIFT_H_
#define _Z_OBJ_LUPYGAMELIFT_H_

#include <global.h>

struct ObjLupygamelift;

typedef struct ObjLupygamelift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x30];
} ObjLupygamelift; // size = 0x174

extern const ActorInit Obj_Lupygamelift_InitVars;

#endif

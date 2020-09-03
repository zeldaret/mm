#ifndef _Z_OBJ_SNOWBALL2_H_
#define _Z_OBJ_SNOWBALL2_H_

#include <global.h>

struct ObjSnowball2;

typedef struct ObjSnowball2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x70];
} ObjSnowball2; // size = 0x1B4

extern const ActorInit Obj_Snowball2_InitVars;

#endif

#ifndef _Z_OBJ_HUGEBOMBIWA_H_
#define _Z_OBJ_HUGEBOMBIWA_H_

#include <global.h>

struct ObjHugebombiwa;

typedef struct ObjHugebombiwa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x374];
} ObjHugebombiwa; // size = 0x4B8

extern const ActorInit Obj_Hugebombiwa_InitVars;

#endif

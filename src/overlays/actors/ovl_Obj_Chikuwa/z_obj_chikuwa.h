#ifndef _Z_OBJ_CHIKUWA_H_
#define _Z_OBJ_CHIKUWA_H_

#include <global.h>

struct ObjChikuwa;

typedef struct ObjChikuwa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x864];
} ObjChikuwa; // size = 0x9A8

extern const ActorInit Obj_Chikuwa_InitVars;

#endif

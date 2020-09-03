#ifndef _Z_OBJ_BOMBIWA_H_
#define _Z_OBJ_BOMBIWA_H_

#include <global.h>

struct ObjBombiwa;

typedef struct ObjBombiwa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC4];
} ObjBombiwa; // size = 0x208

extern const ActorInit Obj_Bombiwa_InitVars;

#endif

#ifndef _Z_OBJ_BIGICICLE_H_
#define _Z_OBJ_BIGICICLE_H_

#include <global.h>

struct ObjBigicicle;

typedef struct ObjBigicicle {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xA0];
} ObjBigicicle; // size = 0x1E4

extern const ActorInit Obj_Bigicicle_InitVars;

#endif

#ifndef Z_OBJ_COMB_H
#define Z_OBJ_COMB_H

#include "global.h"

struct ObjComb;

typedef struct ObjComb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x78];
} ObjComb; // size = 0x1BC

extern const ActorInit Obj_Comb_InitVars;

#endif // Z_OBJ_COMB_H

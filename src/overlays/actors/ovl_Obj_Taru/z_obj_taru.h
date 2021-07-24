#ifndef Z_OBJ_TARU_H
#define Z_OBJ_TARU_H

#include "global.h"

struct ObjTaru;

typedef struct ObjTaru {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} ObjTaru; // size = 0x1B0

extern const ActorInit Obj_Taru_InitVars;

#endif // Z_OBJ_TARU_H

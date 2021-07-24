#ifndef Z_OBJ_MURE3_H
#define Z_OBJ_MURE3_H

#include "global.h"

struct ObjMure3;

typedef struct ObjMure3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} ObjMure3; // size = 0x168

extern const ActorInit Obj_Mure3_InitVars;

#endif // Z_OBJ_MURE3_H

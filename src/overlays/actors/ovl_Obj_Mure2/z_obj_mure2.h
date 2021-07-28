#ifndef Z_OBJ_MURE2_H
#define Z_OBJ_MURE2_H

#include "global.h"

struct ObjMure2;

typedef struct ObjMure2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3C];
} ObjMure2; // size = 0x180

extern const ActorInit Obj_Mure2_InitVars;

#endif // Z_OBJ_MURE2_H

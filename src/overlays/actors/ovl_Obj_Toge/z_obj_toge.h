#ifndef Z_OBJ_TOGE_H
#define Z_OBJ_TOGE_H

#include "global.h"

struct ObjToge;

typedef struct ObjToge {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8C];
} ObjToge; // size = 0x1D0

extern const ActorInit Obj_Toge_InitVars;

#endif // Z_OBJ_TOGE_H

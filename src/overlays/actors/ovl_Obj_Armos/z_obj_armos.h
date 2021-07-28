#ifndef Z_OBJ_ARMOS_H
#define Z_OBJ_ARMOS_H

#include "global.h"

struct ObjArmos;

typedef struct ObjArmos {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x130];
} ObjArmos; // size = 0x274

extern const ActorInit Obj_Armos_InitVars;

#endif // Z_OBJ_ARMOS_H

#ifndef Z_OBJ_MURE_H
#define Z_OBJ_MURE_H

#include "global.h"

struct ObjMure;

typedef struct ObjMure {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x60];
} ObjMure; // size = 0x1A4

extern const ActorInit Obj_Mure_InitVars;

#endif // Z_OBJ_MURE_H

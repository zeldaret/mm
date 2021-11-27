#ifndef Z_OBJ_MAKEKINSUTA_H
#define Z_OBJ_MAKEKINSUTA_H

#include "global.h"

struct ObjMakekinsuta;

typedef struct ObjMakekinsuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} ObjMakekinsuta; // size = 0x148

extern const ActorInit Obj_Makekinsuta_InitVars;

#endif // Z_OBJ_MAKEKINSUTA_H

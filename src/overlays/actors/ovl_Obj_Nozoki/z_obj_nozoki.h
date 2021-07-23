#ifndef Z_OBJ_NOZOKI_H
#define Z_OBJ_NOZOKI_H

#include "global.h"

struct ObjNozoki;

typedef struct ObjNozoki {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} ObjNozoki; // size = 0x164

extern const ActorInit Obj_Nozoki_InitVars;

#endif // Z_OBJ_NOZOKI_H

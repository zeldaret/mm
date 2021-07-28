#ifndef Z_OBJ_KZSAKU_H
#define Z_OBJ_KZSAKU_H

#include "global.h"

struct ObjKzsaku;

typedef struct ObjKzsaku {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x28];
} ObjKzsaku; // size = 0x16C

extern const ActorInit Obj_Kzsaku_InitVars;

#endif // Z_OBJ_KZSAKU_H

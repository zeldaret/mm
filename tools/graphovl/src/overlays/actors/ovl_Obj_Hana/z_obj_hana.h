#ifndef Z_OBJ_HANA_H
#define Z_OBJ_HANA_H

#include "global.h"

struct ObjHana;

typedef struct ObjHana {
    /* 0x000 */ Actor actor;
} ObjHana; // size = 0x144

extern const ActorInit Obj_Hana_InitVars;

#endif // Z_OBJ_HANA_H

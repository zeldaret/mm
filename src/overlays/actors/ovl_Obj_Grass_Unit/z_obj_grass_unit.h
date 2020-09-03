#ifndef _Z_OBJ_GRASS_UNIT_H_
#define _Z_OBJ_GRASS_UNIT_H_

#include <global.h>

struct ObjGrassUnit;

typedef struct ObjGrassUnit {
    /* 0x000 */ Actor actor;
} ObjGrassUnit; // size = 0x144

extern const ActorInit Obj_Grass_Unit_InitVars;

#endif

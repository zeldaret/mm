#ifndef _Z_OBJ_GRASS_H_
#define _Z_OBJ_GRASS_H_

#include <global.h>

struct ObjGrass;

typedef struct ObjGrass {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x315C];
} ObjGrass; // size = 0x32A0

extern const ActorInit Obj_Grass_InitVars;

#endif

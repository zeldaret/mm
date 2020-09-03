#ifndef _Z_OBJ_FIRESHIELD_H_
#define _Z_OBJ_FIRESHIELD_H_

#include <global.h>

struct ObjFireshield;

typedef struct ObjFireshield {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x68];
} ObjFireshield; // size = 0x1AC

extern const ActorInit Obj_Fireshield_InitVars;

#endif

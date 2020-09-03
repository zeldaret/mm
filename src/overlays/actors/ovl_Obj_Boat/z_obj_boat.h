#ifndef _Z_OBJ_BOAT_H_
#define _Z_OBJ_BOAT_H_

#include <global.h>

struct ObjBoat;

typedef struct ObjBoat {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} ObjBoat; // size = 0x168

extern const ActorInit Obj_Boat_InitVars;

#endif

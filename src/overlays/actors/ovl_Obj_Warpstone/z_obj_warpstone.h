#ifndef Z_OBJ_WARPSTONE_H
#define Z_OBJ_WARPSTONE_H

#include <global.h>

struct ObjWarpstone;

typedef struct ObjWarpstone {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} ObjWarpstone; // size = 0x1B0

extern const ActorInit Obj_Warpstone_InitVars;

#endif // Z_OBJ_WARPSTONE_H

#ifndef _Z_OBJ_WARPSTONE_H_
#define _Z_OBJ_WARPSTONE_H_

#include <global.h>

struct ObjWarpstone;

typedef struct ObjWarpstone {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} ObjWarpstone; // size = 0x1B0

extern const ActorInit Obj_Warpstone_InitVars;

#endif

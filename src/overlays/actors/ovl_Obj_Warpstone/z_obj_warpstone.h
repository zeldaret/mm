#ifndef Z_OBJ_WARPSTONE_H
#define Z_OBJ_WARPSTONE_H

#include "global.h"

struct ObjWarpstone;

typedef void (*ObjWarpstoneActionFunc)(struct ObjWarpstone* this, GlobalContext* globalCtx);

typedef struct ObjWarpstone {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x68];
    /* 0x01AC */ ObjWarpstoneActionFunc actionFunc;
} ObjWarpstone; // size = 0x1B0

extern const ActorInit Obj_Warpstone_InitVars;

#endif // Z_OBJ_WARPSTONE_H

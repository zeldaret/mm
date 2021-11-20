#ifndef Z_OBJ_WTURN_H
#define Z_OBJ_WTURN_H

#include "global.h"

struct ObjWturn;

typedef void (*ObjWturnActionFunc)(struct ObjWturn*, GlobalContext*);

typedef struct ObjWturn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjWturnActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x4];
} ObjWturn; // size = 0x14C

extern const ActorInit Obj_Wturn_InitVars;

#endif // Z_OBJ_WTURN_H

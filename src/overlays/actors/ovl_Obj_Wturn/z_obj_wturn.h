#ifndef Z_OBJ_WTURN_H
#define Z_OBJ_WTURN_H

#include "global.h"

struct ObjWturn;

typedef void (*ObjWturnActionFunc)(struct ObjWturn*, GlobalContext*);

typedef struct ObjWturn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjWturnActionFunc actionFunc;
    /* 0x0148 */ s16 camId;
    /* 0x014A */ s16 unk_14A;
} ObjWturn; // size = 0x14C

extern const ActorInit Obj_Wturn_InitVars;

#endif // Z_OBJ_WTURN_H

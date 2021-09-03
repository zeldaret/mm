#ifndef Z_OBJ_FLOWERPOT_H
#define Z_OBJ_FLOWERPOT_H

#include "global.h"

struct ObjFlowerpot;

typedef void (*ObjFlowerpotActionFunc)(struct ObjFlowerpot*, GlobalContext*);

typedef struct ObjFlowerpot {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xA0];
    /* 0x01E4 */ ObjFlowerpotActionFunc actionFunc;
    /* 0x01E8 */ char unk_1E8[0x8];
} ObjFlowerpot; // size = 0x1F0

extern const ActorInit Obj_Flowerpot_InitVars;

#endif // Z_OBJ_FLOWERPOT_H

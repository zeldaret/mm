#ifndef _Z_OBJ_FLOWERPOT_H_
#define _Z_OBJ_FLOWERPOT_H_

#include <global.h>

struct ObjFlowerpot;

typedef struct ObjFlowerpot {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xAC];
} ObjFlowerpot; // size = 0x1F0

extern const ActorInit Obj_Flowerpot_InitVars;

#endif

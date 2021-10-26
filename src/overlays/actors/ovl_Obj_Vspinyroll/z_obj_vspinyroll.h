#ifndef Z_OBJ_VSPINYROLL_H
#define Z_OBJ_VSPINYROLL_H

#include "global.h"

struct ObjVspinyroll;

typedef void (*ObjVspinyrollActionFunc)(struct ObjVspinyroll*, GlobalContext*);

typedef struct ObjVspinyroll {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x24C];
    /* 0x0390 */ ObjVspinyrollActionFunc actionFunc;
    /* 0x0394 */ char unk_394[0x38];
} ObjVspinyroll; // size = 0x3CC

extern const ActorInit Obj_Vspinyroll_InitVars;

#endif // Z_OBJ_VSPINYROLL_H

#ifndef Z_OBJ_HARIKO_H
#define Z_OBJ_HARIKO_H

#include "global.h"

struct ObjHariko;

typedef void (*ObjHarikoActionFunc)(struct ObjHariko*, GlobalContext*);

typedef struct ObjHariko {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjHarikoActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x10];
} ObjHariko; // size = 0x158

extern const ActorInit Obj_Hariko_InitVars;

#endif // Z_OBJ_HARIKO_H

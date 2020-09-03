#ifndef _Z_OBJ_DHOUSE_H_
#define _Z_OBJ_DHOUSE_H_

#include <global.h>

struct ObjDhouse;

typedef struct ObjDhouse {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x1230];
} ObjDhouse; // size = 0x1374

extern const ActorInit Obj_Dhouse_InitVars;

#endif

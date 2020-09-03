#ifndef _Z_OBJ_MINE_H_
#define _Z_OBJ_MINE_H_

#include <global.h>

struct ObjMine;

typedef struct ObjMine {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x1270];
} ObjMine; // size = 0x13B4

extern const ActorInit Obj_Mine_InitVars;

#endif

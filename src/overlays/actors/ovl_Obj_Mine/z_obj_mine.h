#ifndef Z_OBJ_MINE_H
#define Z_OBJ_MINE_H

#include <global.h>

struct ObjMine;

typedef struct ObjMine {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x1270];
} ObjMine; // size = 0x13B4

extern const ActorInit Obj_Mine_InitVars;

#endif // Z_OBJ_MINE_H

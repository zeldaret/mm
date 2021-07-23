#ifndef Z_OBJ_TREE_H
#define Z_OBJ_TREE_H

#include "global.h"

struct ObjTree;

typedef struct ObjTree {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x74];
} ObjTree; // size = 0x1B8

extern const ActorInit Obj_Tree_InitVars;

#endif // Z_OBJ_TREE_H

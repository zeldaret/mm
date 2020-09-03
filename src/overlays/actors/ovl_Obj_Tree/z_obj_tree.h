#ifndef _Z_OBJ_TREE_H_
#define _Z_OBJ_TREE_H_

#include <global.h>

struct ObjTree;

typedef struct ObjTree {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x74];
} ObjTree; // size = 0x1B8

extern const ActorInit Obj_Tree_InitVars;

#endif

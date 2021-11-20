#ifndef Z_OBJ_TREE_H
#define Z_OBJ_TREE_H

#include "global.h"

struct ObjTree;

typedef void (*ObjTreeActionFunc)(struct ObjTree*, GlobalContext*);

typedef struct ObjTree {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x64];
    /* 0x01A8 */ ObjTreeActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0xC];
} ObjTree; // size = 0x1B8

extern const ActorInit Obj_Tree_InitVars;

#endif // Z_OBJ_TREE_H

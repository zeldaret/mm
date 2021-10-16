#ifndef Z_OBJ_TREE_H
#define Z_OBJ_TREE_H

#include "global.h"

struct ObjTree;

typedef void (*ObjTreeActionFunc)(struct ObjTree*, GlobalContext*);

typedef struct ObjTree {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderCylinder collider;
    /* 0x01A8 */ ObjTreeActionFunc actionFunc;
    /* 0x01AC */ f32 swayAmplitude;
    /* 0x01B0 */ s16 swayAngle;
    /* 0x01B2 */ s16 swayVelocity;
    /* 0x01B4 */ s16 timer;
} ObjTree; // size = 0x1B8

extern const ActorInit Obj_Tree_InitVars;

#endif // Z_OBJ_TREE_H

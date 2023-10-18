#ifndef Z_OBJ_TAKARAYA_WALL_H
#define Z_OBJ_TAKARAYA_WALL_H

#include "global.h"

struct ObjTakarayaWall;

typedef void (*ObjTakarayaWallActionFunc)(struct ObjTakarayaWall*, PlayState*);

typedef struct ObjTakarayaWall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ObjTakarayaWallActionFunc actionFunc;
    /* 0x148 */ ColliderCylinder unk148;
    /* 0x194 */ ColliderCylinder unk194;
} ObjTakarayaWall; // size = 0x1E0

#endif // Z_OBJ_TAKARAYA_WALL_H

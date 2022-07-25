#ifndef Z_OBJ_TAKARAYA_WALL_H
#define Z_OBJ_TAKARAYA_WALL_H

#include "global.h"

struct ObjTakarayaWall;

typedef void (*ObjTakarayaWallActionFunc)(struct ObjTakarayaWall*, PlayState*);

typedef struct ObjTakarayaWall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ObjTakarayaWallActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x98];
} ObjTakarayaWall; // size = 0x1E0

extern const ActorInit Obj_Takaraya_Wall_InitVars;

#endif // Z_OBJ_TAKARAYA_WALL_H

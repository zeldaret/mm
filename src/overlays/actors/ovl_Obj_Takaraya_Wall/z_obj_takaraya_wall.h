#ifndef Z_OBJ_TAKARAYA_WALL_H
#define Z_OBJ_TAKARAYA_WALL_H

#include <global.h>

struct ObjTakarayaWall;

typedef struct ObjTakarayaWall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x9C];
} ObjTakarayaWall; // size = 0x1E0

extern const ActorInit Obj_Takaraya_Wall_InitVars;

#endif // Z_OBJ_TAKARAYA_WALL_H

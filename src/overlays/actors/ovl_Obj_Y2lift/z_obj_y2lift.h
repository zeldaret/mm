#ifndef Z_OBJ_Y2LIFT_H
#define Z_OBJ_Y2LIFT_H

#include <global.h>

struct ObjY2lift;

typedef struct ObjY2lift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C];
} ObjY2lift; // size = 0x160

extern const ActorInit Obj_Y2lift_InitVars;

#endif // Z_OBJ_Y2LIFT_H

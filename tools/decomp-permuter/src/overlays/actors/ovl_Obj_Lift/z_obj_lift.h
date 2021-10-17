#ifndef Z_OBJ_LIFT_H
#define Z_OBJ_LIFT_H

#include <global.h>

struct ObjLift;

typedef struct ObjLift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x38];
} ObjLift; // size = 0x17C

extern const ActorInit Obj_Lift_InitVars;

#endif // Z_OBJ_LIFT_H

#ifndef Z_OBJ_LIFT_H
#define Z_OBJ_LIFT_H

#include "global.h"

struct ObjLift;

typedef void (*ObjLiftActionFunc)(struct ObjLift*, GlobalContext*);

typedef struct ObjLift {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjLiftActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x1C];
} ObjLift; // size = 0x17C

extern const ActorInit Obj_Lift_InitVars;

#endif // Z_OBJ_LIFT_H

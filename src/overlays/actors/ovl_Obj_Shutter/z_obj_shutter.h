#ifndef Z_OBJ_SHUTTER_H
#define Z_OBJ_SHUTTER_H

#include "global.h"

struct ObjShutter;

typedef struct ObjShutter {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 schedule;
    /* 0x148 */ f32 velocity;
} ObjShutter; // size = 0x14C

extern const ActorInit Obj_Shutter_InitVars;

#endif // Z_OBJ_SHUTTER_H

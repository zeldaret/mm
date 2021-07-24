#ifndef Z_OBJ_Y2SHUTTER_H
#define Z_OBJ_Y2SHUTTER_H

#include "global.h"

struct ObjY2shutter;

typedef struct ObjY2shutter {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C];
} ObjY2shutter; // size = 0x160

extern const ActorInit Obj_Y2shutter_InitVars;

#endif // Z_OBJ_Y2SHUTTER_H

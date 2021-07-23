#ifndef Z_OBJ_SWITCH_H
#define Z_OBJ_SWITCH_H

#include "global.h"

struct ObjSwitch;

typedef struct ObjSwitch {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x114];
} ObjSwitch; // size = 0x258

extern const ActorInit Obj_Switch_InitVars;

#endif // Z_OBJ_SWITCH_H

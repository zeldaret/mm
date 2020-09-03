#ifndef _Z_OBJ_SWITCH_H_
#define _Z_OBJ_SWITCH_H_

#include <global.h>

struct ObjSwitch;

typedef struct ObjSwitch {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x114];
} ObjSwitch; // size = 0x258

extern const ActorInit Obj_Switch_InitVars;

#endif

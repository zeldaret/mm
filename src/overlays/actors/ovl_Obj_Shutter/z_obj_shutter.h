#ifndef _Z_OBJ_SHUTTER_H_
#define _Z_OBJ_SHUTTER_H_

#include <global.h>

struct ObjShutter;

typedef struct ObjShutter {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} ObjShutter; // size = 0x14C

extern const ActorInit Obj_Shutter_InitVars;

#endif

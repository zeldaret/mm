#ifndef _Z_OBJ_BOYO_H_
#define _Z_OBJ_BOYO_H_

#include <global.h>

struct ObjBoyo;

typedef struct ObjBoyo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} ObjBoyo; // size = 0x1B0

extern const ActorInit Obj_Boyo_InitVars;

#endif

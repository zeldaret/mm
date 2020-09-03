#ifndef _Z_OBJ_TOGE_H_
#define _Z_OBJ_TOGE_H_

#include <global.h>

struct ObjToge;

typedef struct ObjToge {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8C];
} ObjToge; // size = 0x1D0

extern const ActorInit Obj_Toge_InitVars;

#endif

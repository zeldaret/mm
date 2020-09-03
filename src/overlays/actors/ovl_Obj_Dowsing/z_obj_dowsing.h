#ifndef _Z_OBJ_DOWSING_H_
#define _Z_OBJ_DOWSING_H_

#include <global.h>

struct ObjDowsing;

typedef struct ObjDowsing {
    /* 0x000 */ Actor actor;
} ObjDowsing; // size = 0x144

extern const ActorInit Obj_Dowsing_InitVars;

#endif

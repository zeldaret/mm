#ifndef _Z_OBJ_HAMISHI_H_
#define _Z_OBJ_HAMISHI_H_

#include <global.h>

struct ObjHamishi;

typedef struct ObjHamishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x60];
} ObjHamishi; // size = 0x1A4

extern const ActorInit Obj_Hamishi_InitVars;

#endif

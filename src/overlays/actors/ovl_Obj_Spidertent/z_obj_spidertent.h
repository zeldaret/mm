#ifndef _Z_OBJ_SPIDERTENT_H_
#define _Z_OBJ_SPIDERTENT_H_

#include <global.h>

struct ObjSpidertent;

typedef struct ObjSpidertent {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x288];
} ObjSpidertent; // size = 0x3CC

extern const ActorInit Obj_Spidertent_InitVars;

#endif

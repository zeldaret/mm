#ifndef Z_OBJ_SPIDERTENT_H
#define Z_OBJ_SPIDERTENT_H

#include <global.h>

struct ObjSpidertent;

typedef struct ObjSpidertent {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x288];
} ObjSpidertent; // size = 0x3CC

extern const ActorInit Obj_Spidertent_InitVars;

#endif // Z_OBJ_SPIDERTENT_H

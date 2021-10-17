#ifndef Z_OBJ_JG_GAKKI_H
#define Z_OBJ_JG_GAKKI_H

#include "global.h"

struct ObjJgGakki;

typedef struct ObjJgGakki {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x90];
} ObjJgGakki; // size = 0x1D4

extern const ActorInit Obj_Jg_Gakki_InitVars;

#endif // Z_OBJ_JG_GAKKI_H

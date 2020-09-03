#ifndef _Z_OBJ_MURE2_H_
#define _Z_OBJ_MURE2_H_

#include <global.h>

struct ObjMure2;

typedef struct ObjMure2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3C];
} ObjMure2; // size = 0x180

extern const ActorInit Obj_Mure2_InitVars;

#endif

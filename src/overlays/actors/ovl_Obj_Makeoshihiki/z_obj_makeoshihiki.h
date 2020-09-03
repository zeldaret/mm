#ifndef _Z_OBJ_MAKEOSHIHIKI_H_
#define _Z_OBJ_MAKEOSHIHIKI_H_

#include <global.h>

struct ObjMakeoshihiki;

typedef struct ObjMakeoshihiki {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} ObjMakeoshihiki; // size = 0x14C

extern const ActorInit Obj_Makeoshihiki_InitVars;

#endif

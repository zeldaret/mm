#ifndef _Z_OBJ_ROTLIFT_H_
#define _Z_OBJ_ROTLIFT_H_

#include <global.h>

struct ObjRotlift;

typedef struct ObjRotlift {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} ObjRotlift; // size = 0x164

extern const ActorInit Obj_Rotlift_InitVars;

#endif

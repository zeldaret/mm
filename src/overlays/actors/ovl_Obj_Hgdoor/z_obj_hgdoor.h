#ifndef _Z_OBJ_HGDOOR_H_
#define _Z_OBJ_HGDOOR_H_

#include <global.h>

struct ObjHgdoor;

typedef struct ObjHgdoor {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} ObjHgdoor; // size = 0x168

extern const ActorInit Obj_Hgdoor_InitVars;

#endif

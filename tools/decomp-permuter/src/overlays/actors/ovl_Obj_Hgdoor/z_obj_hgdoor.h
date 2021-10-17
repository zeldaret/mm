#ifndef Z_OBJ_HGDOOR_H
#define Z_OBJ_HGDOOR_H

#include <global.h>

struct ObjHgdoor;

typedef struct ObjHgdoor {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} ObjHgdoor; // size = 0x168

extern const ActorInit Obj_Hgdoor_InitVars;

#endif // Z_OBJ_HGDOOR_H

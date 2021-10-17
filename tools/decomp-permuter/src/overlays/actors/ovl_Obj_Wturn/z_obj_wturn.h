#ifndef Z_OBJ_WTURN_H
#define Z_OBJ_WTURN_H

#include <global.h>

struct ObjWturn;

typedef struct ObjWturn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} ObjWturn; // size = 0x14C

extern const ActorInit Obj_Wturn_InitVars;

#endif // Z_OBJ_WTURN_H

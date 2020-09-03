#ifndef Z_OBJ_GHAKA_H
#define Z_OBJ_GHAKA_H

#include <global.h>

struct ObjGhaka;

typedef struct ObjGhaka {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x28];
} ObjGhaka; // size = 0x16C

extern const ActorInit Obj_Ghaka_InitVars;

#endif // Z_OBJ_GHAKA_H

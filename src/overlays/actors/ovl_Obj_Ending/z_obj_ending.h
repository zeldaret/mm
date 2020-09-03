#ifndef Z_OBJ_ENDING_H
#define Z_OBJ_ENDING_H

#include <global.h>

struct ObjEnding;

typedef struct ObjEnding {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} ObjEnding; // size = 0x14C

extern const ActorInit Obj_Ending_InitVars;

#endif // Z_OBJ_ENDING_H

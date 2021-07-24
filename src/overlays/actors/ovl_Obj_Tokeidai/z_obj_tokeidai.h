#ifndef Z_OBJ_TOKEIDAI_H
#define Z_OBJ_TOKEIDAI_H

#include "global.h"

struct ObjTokeidai;

typedef struct ObjTokeidai {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x34];
} ObjTokeidai; // size = 0x178

extern const ActorInit Obj_Tokeidai_InitVars;

#endif // Z_OBJ_TOKEIDAI_H

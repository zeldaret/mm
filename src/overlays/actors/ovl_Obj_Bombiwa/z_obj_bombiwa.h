#ifndef Z_OBJ_BOMBIWA_H
#define Z_OBJ_BOMBIWA_H

#include "global.h"

struct ObjBombiwa;

typedef struct ObjBombiwa {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC4];
} ObjBombiwa; // size = 0x208

extern const ActorInit Obj_Bombiwa_InitVars;

#endif // Z_OBJ_BOMBIWA_H

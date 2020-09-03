#ifndef Z_OBJ_TSUBO_H
#define Z_OBJ_TSUBO_H

#include <global.h>

struct ObjTsubo;

typedef struct ObjTsubo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x58];
} ObjTsubo; // size = 0x19C

extern const ActorInit Obj_Tsubo_InitVars;

#endif // Z_OBJ_TSUBO_H

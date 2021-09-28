#ifndef Z_OBJ_TSUBO_H
#define Z_OBJ_TSUBO_H

#include "global.h"

struct ObjTsubo;

typedef void (*ObjTsuboActionFunc)(struct ObjTsubo*, GlobalContext*);

typedef struct ObjTsubo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjTsuboActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x53];
    /* 0x019B */ u8 unk19B;
} ObjTsubo; // size = 0x19C

extern const ActorInit Obj_Tsubo_InitVars;

#endif // Z_OBJ_TSUBO_H

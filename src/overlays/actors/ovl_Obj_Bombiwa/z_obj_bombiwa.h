#ifndef Z_OBJ_BOMBIWA_H
#define Z_OBJ_BOMBIWA_H

#include "global.h"

struct ObjBombiwa;

typedef void (*ObjBombiwaActionFunc)(struct ObjBombiwa* this, GlobalContext* globalCtx);

typedef struct ObjBombiwa {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xC0];
    /* 0x0204 */ ObjBombiwaActionFunc actionFunc;
} ObjBombiwa; // size = 0x208

extern const ActorInit Obj_Bombiwa_InitVars;

#endif // Z_OBJ_BOMBIWA_H

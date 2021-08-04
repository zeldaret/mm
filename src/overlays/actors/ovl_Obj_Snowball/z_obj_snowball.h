#ifndef Z_OBJ_SNOWBALL_H
#define Z_OBJ_SNOWBALL_H

#include "global.h"

struct ObjSnowball;

typedef void (*ObjSnowballActionFunc)(struct ObjSnowball* this, GlobalContext* globalCtx);

typedef struct ObjSnowball {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x60];
    /* 0x01A4 */ ObjSnowballActionFunc actionFunc;
    /* 0x01A8 */ char unk_1A8[0x6C];
} ObjSnowball; // size = 0x214

extern const ActorInit Obj_Snowball_InitVars;

#endif // Z_OBJ_SNOWBALL_H

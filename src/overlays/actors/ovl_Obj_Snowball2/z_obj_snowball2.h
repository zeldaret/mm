#ifndef Z_OBJ_SNOWBALL2_H
#define Z_OBJ_SNOWBALL2_H

#include "global.h"

struct ObjSnowball2;

typedef void (*ObjSnowball2ActionFunc)(struct ObjSnowball2* this, GlobalContext* globalCtx);

typedef struct ObjSnowball2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x60];
    /* 0x01A4 */ ObjSnowball2ActionFunc actionFunc;
    /* 0x01A8 */ char unk_1A8[0xC];
} ObjSnowball2; // size = 0x1B4

extern const ActorInit Obj_Snowball2_InitVars;

#endif // Z_OBJ_SNOWBALL2_H

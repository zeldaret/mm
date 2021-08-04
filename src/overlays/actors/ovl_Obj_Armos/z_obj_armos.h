#ifndef Z_OBJ_ARMOS_H
#define Z_OBJ_ARMOS_H

#include "global.h"

struct ObjArmos;

typedef void (*ObjArmosActionFunc)(struct ObjArmos* this, GlobalContext* globalCtx);

typedef struct ObjArmos {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x104];
    /* 0x0248 */ ObjArmosActionFunc actionFunc;
    /* 0x024C */ char unk_24C[0x28];
} ObjArmos; // size = 0x274

extern const ActorInit Obj_Armos_InitVars;

#endif // Z_OBJ_ARMOS_H

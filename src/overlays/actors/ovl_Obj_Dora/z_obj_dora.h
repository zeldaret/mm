#ifndef Z_OBJ_DORA_H
#define Z_OBJ_DORA_H

#include "global.h"

struct ObjDora;

typedef void (*ObjDoraActionFunc)(struct ObjDora* this, GlobalContext* globalCtx);

typedef struct ObjDora {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x248];
    /* 0x038C */ ObjDoraActionFunc actionFunc;
    /* 0x0390 */ char unk_390[0x1C];
} ObjDora; // size = 0x3AC

extern const ActorInit Obj_Dora_InitVars;

#endif // Z_OBJ_DORA_H

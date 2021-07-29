#ifndef Z_OBJ_TOKEIDAI_H
#define Z_OBJ_TOKEIDAI_H

#include "global.h"

struct ObjTokeidai;

typedef void (*ObjTokeidaiActionFunc)(struct ObjTokeidai* this, GlobalContext* globalCtx);

typedef struct ObjTokeidai {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x30];
    /* 0x0174 */ ObjTokeidaiActionFunc actionFunc;
} ObjTokeidai; // size = 0x178

extern const ActorInit Obj_Tokeidai_InitVars;

#endif // Z_OBJ_TOKEIDAI_H

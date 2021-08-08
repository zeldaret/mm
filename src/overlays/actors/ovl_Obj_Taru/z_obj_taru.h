#ifndef Z_OBJ_TARU_H
#define Z_OBJ_TARU_H

#include "global.h"

struct ObjTaru;

typedef void (*ObjTaruActionFunc)(struct ObjTaru* this, GlobalContext* globalCtx);

typedef struct ObjTaru {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x64];
    /* 0x01A8 */ ObjTaruActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0x4];
} ObjTaru; // size = 0x1B0

extern const ActorInit Obj_Taru_InitVars;

#endif // Z_OBJ_TARU_H

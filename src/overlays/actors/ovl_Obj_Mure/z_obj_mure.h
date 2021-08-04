#ifndef Z_OBJ_MURE_H
#define Z_OBJ_MURE_H

#include "global.h"

struct ObjMure;

typedef void (*ObjMureActionFunc)(struct ObjMure* this, GlobalContext* globalCtx);

typedef struct ObjMure {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjMureActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x5C];
} ObjMure; // size = 0x1A4

extern const ActorInit Obj_Mure_InitVars;

#endif // Z_OBJ_MURE_H

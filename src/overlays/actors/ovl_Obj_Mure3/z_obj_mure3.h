#ifndef Z_OBJ_MURE3_H
#define Z_OBJ_MURE3_H

#include "global.h"

struct ObjMure3;

typedef void (*ObjMure3ActionFunc)(struct ObjMure3*, GlobalContext*);

typedef struct ObjMure3 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjMure3ActionFunc actionFunc;
    /* 0x0148 */ char unk_148[0x20];
} ObjMure3; // size = 0x168

extern const ActorInit Obj_Mure3_InitVars;

#endif // Z_OBJ_MURE3_H

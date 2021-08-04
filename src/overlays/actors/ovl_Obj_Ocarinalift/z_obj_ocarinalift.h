#ifndef Z_OBJ_OCARINALIFT_H
#define Z_OBJ_OCARINALIFT_H

#include "global.h"

struct ObjOcarinalift;

typedef void (*ObjOcarinaliftActionFunc)(struct ObjOcarinalift* this, GlobalContext* globalCtx);

typedef struct ObjOcarinalift {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjOcarinaliftActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x18];
} ObjOcarinalift; // size = 0x178

extern const ActorInit Obj_Ocarinalift_InitVars;

#endif // Z_OBJ_OCARINALIFT_H

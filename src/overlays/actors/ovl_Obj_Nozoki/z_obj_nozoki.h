#ifndef Z_OBJ_NOZOKI_H
#define Z_OBJ_NOZOKI_H

#include "global.h"

struct ObjNozoki;

typedef void (*ObjNozokiActionFunc)(struct ObjNozoki* this, GlobalContext* globalCtx);

typedef struct ObjNozoki {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C];
    /* 0x0160 */ ObjNozokiActionFunc actionFunc;
} ObjNozoki; // size = 0x164

extern const ActorInit Obj_Nozoki_InitVars;

#endif // Z_OBJ_NOZOKI_H

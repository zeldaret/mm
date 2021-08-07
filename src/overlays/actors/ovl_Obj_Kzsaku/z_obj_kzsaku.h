#ifndef Z_OBJ_KZSAKU_H
#define Z_OBJ_KZSAKU_H

#include "global.h"

struct ObjKzsaku;

typedef void (*ObjKzsakuActionFunc)(struct ObjKzsaku* this, GlobalContext* globalCtx);

typedef struct ObjKzsaku {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ ObjKzsakuActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0xC];
} ObjKzsaku; // size = 0x16C

extern const ActorInit Obj_Kzsaku_InitVars;

#endif // Z_OBJ_KZSAKU_H

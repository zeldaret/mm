#ifndef Z_OBJ_SPIDERTENT_H
#define Z_OBJ_SPIDERTENT_H

#include "global.h"

struct ObjSpidertent;

typedef void (*ObjSpidertentActionFunc)(struct ObjSpidertent* this, GlobalContext* globalCtx);

typedef struct ObjSpidertent {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x284];
    /* 0x03C8 */ ObjSpidertentActionFunc actionFunc;
} ObjSpidertent; // size = 0x3CC

extern const ActorInit Obj_Spidertent_InitVars;

#endif // Z_OBJ_SPIDERTENT_H

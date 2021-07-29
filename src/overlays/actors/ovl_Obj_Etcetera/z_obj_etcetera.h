#ifndef Z_OBJ_ETCETERA_H
#define Z_OBJ_ETCETERA_H

#include "global.h"

struct ObjEtcetera;

typedef void (*ObjEtceteraActionFunc)(struct ObjEtcetera* this, GlobalContext* globalCtx);

typedef struct ObjEtcetera {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x13C];
    /* 0x0280 */ ObjEtceteraActionFunc actionFunc;
} ObjEtcetera; // size = 0x284

extern const ActorInit Obj_Etcetera_InitVars;

#endif // Z_OBJ_ETCETERA_H

#ifndef Z_OBJ_CHAN_H
#define Z_OBJ_CHAN_H

#include "global.h"

struct ObjChan;

typedef void (*ObjChanActionFunc)(struct ObjChan* this, GlobalContext* globalCtx);

typedef struct ObjChan {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ObjChanActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x9C];
} ObjChan; // size = 0x1E4

extern const ActorInit Obj_Chan_InitVars;

#endif // Z_OBJ_CHAN_H

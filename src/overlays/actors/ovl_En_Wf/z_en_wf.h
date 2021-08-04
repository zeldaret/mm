#ifndef Z_EN_WF_H
#define Z_EN_WF_H

#include "global.h"

struct EnWf;

typedef void (*EnWfActionFunc)(struct EnWf* this, GlobalContext* globalCtx);

typedef struct EnWf {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x14C];
    /* 0x0290 */ EnWfActionFunc actionFunc;
    /* 0x0294 */ char unk_294[0x254];
} EnWf; // size = 0x4E8

extern const ActorInit En_Wf_InitVars;

#endif // Z_EN_WF_H

#ifndef Z_EN_SCOPENUTS_H
#define Z_EN_SCOPENUTS_H

#include "global.h"

struct EnScopenuts;

typedef void (*EnScopenutsActionFunc)(struct EnScopenuts* this, GlobalContext* globalCtx);

typedef struct EnScopenuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x194];
    /* 0x02D8 */ EnScopenutsActionFunc actionFunc;
    /* 0x02DC */ char unk_2DC[0x98];
} EnScopenuts; // size = 0x374

extern const ActorInit En_Scopenuts_InitVars;

#endif // Z_EN_SCOPENUTS_H

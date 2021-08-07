#ifndef Z_EN_YB_H
#define Z_EN_YB_H

#include "global.h"

struct EnYb;

typedef void (*EnYbActionFunc)(struct EnYb* this, GlobalContext* globalCtx);

typedef struct EnYb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x2DC];
    /* 0x0420 */ EnYbActionFunc actionFunc;
} EnYb; // size = 0x424

extern const ActorInit En_Yb_InitVars;

#endif // Z_EN_YB_H

#ifndef Z_EN_AND_H
#define Z_EN_AND_H

#include "global.h"

struct EnAnd;

typedef void (*EnAndActionFunc)(struct EnAnd* this, GlobalContext* globalCtx);

typedef struct EnAnd {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnAndActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x188];
} EnAnd; // size = 0x314

extern const ActorInit En_And_InitVars;

#endif // Z_EN_AND_H

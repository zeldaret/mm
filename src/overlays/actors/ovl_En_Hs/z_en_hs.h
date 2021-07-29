#ifndef Z_EN_HS_H
#define Z_EN_HS_H

#include "global.h"

struct EnHs;

typedef void (*EnHsActionFunc)(struct EnHs* this, GlobalContext* globalCtx);

typedef struct EnHs {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x250];
    /* 0x0394 */ EnHsActionFunc actionFunc;
} EnHs; // size = 0x398

extern const ActorInit En_Hs_InitVars;

#endif // Z_EN_HS_H

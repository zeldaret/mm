#ifndef Z_EN_GUARD_NUTS_H
#define Z_EN_GUARD_NUTS_H

#include "global.h"

struct EnGuardNuts;

typedef void (*EnGuardNutsActionFunc)(struct EnGuardNuts* this, GlobalContext* globalCtx);

typedef struct EnGuardNuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xC8];
    /* 0x020C */ EnGuardNutsActionFunc actionFunc;
    /* 0x0210 */ char unk_210[0x80];
} EnGuardNuts; // size = 0x290

extern const ActorInit En_Guard_Nuts_InitVars;

#endif // Z_EN_GUARD_NUTS_H

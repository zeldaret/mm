#ifndef Z_EN_HIDDEN_NUTS_H
#define Z_EN_HIDDEN_NUTS_H

#include "global.h"

struct EnHiddenNuts;

typedef void (*EnHiddenNutsActionFunc)(struct EnHiddenNuts* this, GlobalContext* globalCtx);

typedef struct EnHiddenNuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xBC];
    /* 0x0200 */ EnHiddenNutsActionFunc actionFunc;
    /* 0x0204 */ char unk_204[0x7C];
} EnHiddenNuts; // size = 0x280

extern const ActorInit En_Hidden_Nuts_InitVars;

#endif // Z_EN_HIDDEN_NUTS_H

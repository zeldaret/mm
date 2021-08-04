#ifndef Z_EN_LIFT_NUTS_H
#define Z_EN_LIFT_NUTS_H

#include "global.h"

struct EnLiftNuts;

typedef void (*EnLiftNutsActionFunc)(struct EnLiftNuts* this, GlobalContext* globalCtx);

typedef struct EnLiftNuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnLiftNutsActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x180];
} EnLiftNuts; // size = 0x358

extern const ActorInit En_Lift_Nuts_InitVars;

#endif // Z_EN_LIFT_NUTS_H

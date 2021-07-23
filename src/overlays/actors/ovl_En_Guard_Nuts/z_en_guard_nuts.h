#ifndef Z_EN_GUARD_NUTS_H
#define Z_EN_GUARD_NUTS_H

#include "global.h"

struct EnGuardNuts;

typedef struct EnGuardNuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x14C];
} EnGuardNuts; // size = 0x290

extern const ActorInit En_Guard_Nuts_InitVars;

#endif // Z_EN_GUARD_NUTS_H

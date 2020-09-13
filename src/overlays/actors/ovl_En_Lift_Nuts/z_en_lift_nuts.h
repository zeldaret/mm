#ifndef Z_EN_LIFT_NUTS_H
#define Z_EN_LIFT_NUTS_H

#include <global.h>

struct EnLiftNuts;

typedef struct EnLiftNuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x214];
} EnLiftNuts; // size = 0x358

extern const ActorInit En_Lift_Nuts_InitVars;

#endif // Z_EN_LIFT_NUTS_H

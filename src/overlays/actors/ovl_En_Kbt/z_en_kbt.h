#ifndef Z_EN_KBT_H
#define Z_EN_KBT_H

#include "global.h"

struct EnKbt;

typedef struct EnKbt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x148];
} EnKbt; // size = 0x28C

extern const ActorInit En_Kbt_InitVars;

#endif // Z_EN_KBT_H

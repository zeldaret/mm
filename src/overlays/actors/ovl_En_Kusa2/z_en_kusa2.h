#ifndef Z_EN_KUSA2_H
#define Z_EN_KUSA2_H

#include "global.h"

struct EnKusa2;

typedef struct EnKusa2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x90];
} EnKusa2; // size = 0x1D4

extern const ActorInit En_Kusa2_InitVars;

#endif // Z_EN_KUSA2_H

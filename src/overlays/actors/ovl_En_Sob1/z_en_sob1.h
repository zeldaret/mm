#ifndef Z_EN_SOB1_H
#define Z_EN_SOB1_H

#include "global.h"

struct EnSob1;

typedef struct EnSob1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x28C];
} EnSob1; // size = 0x3D0

extern const ActorInit En_Sob1_InitVars;

#endif // Z_EN_SOB1_H

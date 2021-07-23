#ifndef Z_EN_GE2_H
#define Z_EN_GE2_H

#include "global.h"

struct EnGe2;

typedef struct EnGe2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C8];
} EnGe2; // size = 0x30C

extern const ActorInit En_Ge2_InitVars;

#endif // Z_EN_GE2_H

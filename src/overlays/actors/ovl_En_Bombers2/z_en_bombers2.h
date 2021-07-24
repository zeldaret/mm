#ifndef Z_EN_BOMBERS2_H
#define Z_EN_BOMBERS2_H

#include "global.h"

struct EnBombers2;

typedef struct EnBombers2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D8];
} EnBombers2; // size = 0x31C

extern const ActorInit En_Bombers2_InitVars;

#endif // Z_EN_BOMBERS2_H

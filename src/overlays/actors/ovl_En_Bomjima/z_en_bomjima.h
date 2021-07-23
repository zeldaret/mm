#ifndef Z_EN_BOMJIMA_H
#define Z_EN_BOMJIMA_H

#include "global.h"

struct EnBomjima;

typedef struct EnBomjima {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x200];
} EnBomjima; // size = 0x344

extern const ActorInit En_Bomjima_InitVars;

#endif // Z_EN_BOMJIMA_H

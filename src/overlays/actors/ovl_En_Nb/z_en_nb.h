#ifndef Z_EN_NB_H
#define Z_EN_NB_H

#include "global.h"

struct EnNb;

typedef struct EnNb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x158];
} EnNb; // size = 0x29C

extern const ActorInit En_Nb_InitVars;

#endif // Z_EN_NB_H

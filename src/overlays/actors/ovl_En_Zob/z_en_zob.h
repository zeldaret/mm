#ifndef Z_EN_ZOB_H
#define Z_EN_ZOB_H

#include "global.h"

struct EnZob;

typedef struct EnZob {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D4];
} EnZob; // size = 0x318

extern const ActorInit En_Zob_InitVars;

#endif // Z_EN_ZOB_H

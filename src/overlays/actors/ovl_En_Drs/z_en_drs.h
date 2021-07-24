#ifndef Z_EN_DRS_H
#define Z_EN_DRS_H

#include "global.h"

struct EnDrs;

typedef struct EnDrs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC8];
} EnDrs; // size = 0x20C

extern const ActorInit En_Drs_InitVars;

#endif // Z_EN_DRS_H

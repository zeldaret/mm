#ifndef Z_EN_DG_H
#define Z_EN_DG_H

#include "global.h"

struct EnDg;

typedef struct EnDg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x15C];
} EnDg; // size = 0x2A0

extern const ActorInit En_Dg_InitVars;

#endif // Z_EN_DG_H

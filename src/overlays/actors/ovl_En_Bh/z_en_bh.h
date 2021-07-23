#ifndef Z_EN_BH_H
#define Z_EN_BH_H

#include "global.h"

struct EnBh;

typedef struct EnBh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xA8];
} EnBh; // size = 0x1EC

extern const ActorInit En_Bh_InitVars;

#endif // Z_EN_BH_H

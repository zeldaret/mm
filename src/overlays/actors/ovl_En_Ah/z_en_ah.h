#ifndef Z_EN_AH_H
#define Z_EN_AH_H

#include "global.h"

struct EnAh;

typedef struct EnAh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C0];
} EnAh; // size = 0x304

extern const ActorInit En_Ah_InitVars;

#endif // Z_EN_AH_H

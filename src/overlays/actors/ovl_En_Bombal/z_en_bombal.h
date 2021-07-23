#ifndef Z_EN_BOMBAL_H
#define Z_EN_BOMBAL_H

#include "global.h"

struct EnBombal;

typedef struct EnBombal {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x2900];
} EnBombal; // size = 0x2A44

extern const ActorInit En_Bombal_InitVars;

#endif // Z_EN_BOMBAL_H

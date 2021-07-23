#ifndef Z_EN_RU_H
#define Z_EN_RU_H

#include "global.h"

struct EnRu;

typedef struct EnRu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x310];
} EnRu; // size = 0x454

extern const ActorInit En_Ru_InitVars;

#endif // Z_EN_RU_H

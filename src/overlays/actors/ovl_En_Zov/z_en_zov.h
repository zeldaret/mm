#ifndef Z_EN_ZOV_H
#define Z_EN_ZOV_H

#include "global.h"

struct EnZov;

typedef struct EnZov {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1F0];
} EnZov; // size = 0x334

extern const ActorInit En_Zov_InitVars;

#endif // Z_EN_ZOV_H

#ifndef Z_BOSS_03_H
#define Z_BOSS_03_H

#include "global.h"

struct Boss03;

typedef struct Boss03 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x438];
} Boss03; // size = 0x57C

extern const ActorInit Boss_03_InitVars;

#endif // Z_BOSS_03_H

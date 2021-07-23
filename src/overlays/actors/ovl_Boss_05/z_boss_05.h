#ifndef Z_BOSS_05_H
#define Z_BOSS_05_H

#include "global.h"

struct Boss05;

typedef struct Boss05 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3C4];
} Boss05; // size = 0x508

extern const ActorInit Boss_05_InitVars;

#endif // Z_BOSS_05_H

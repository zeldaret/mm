#ifndef Z_BOSS_01_H
#define Z_BOSS_01_H

#include "global.h"

struct Boss01;

typedef void (*Boss01ActionFunc)(struct Boss01*, PlayState*);

typedef struct Boss01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x320];
    /* 0x464 */ Boss01ActionFunc actionFunc;
    /* 0x468 */ char unk_468[0x674];
} Boss01; // size = 0xADC

extern const ActorInit Boss_01_InitVars;

#endif // Z_BOSS_01_H

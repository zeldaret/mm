#ifndef Z_BOSS_05_H
#define Z_BOSS_05_H

#include "global.h"

struct Boss05;

typedef void (*Boss05ActionFunc)(struct Boss05*, PlayState*);

typedef struct Boss05 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C];
    /* 0x170 */ Boss05ActionFunc actionFunc;
    /* 0x174 */ char unk_174[0x394];
} Boss05; // size = 0x508

extern const ActorInit Boss_05_InitVars;

#endif // Z_BOSS_05_H

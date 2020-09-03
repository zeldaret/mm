#ifndef _Z_BOSS_05_H_
#define _Z_BOSS_05_H_

#include <global.h>

struct Boss05;

typedef struct Boss05 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3C4];
} Boss05; // size = 0x508

extern const ActorInit Boss_05_InitVars;

#endif

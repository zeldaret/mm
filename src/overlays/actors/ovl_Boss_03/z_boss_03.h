#ifndef _Z_BOSS_03_H_
#define _Z_BOSS_03_H_

#include <global.h>

struct Boss03;

typedef struct Boss03 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x438];
} Boss03; // size = 0x57C

extern const ActorInit Boss_03_InitVars;

#endif

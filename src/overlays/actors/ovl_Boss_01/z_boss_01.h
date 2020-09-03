#ifndef _Z_BOSS_01_H_
#define _Z_BOSS_01_H_

#include <global.h>

struct Boss01;

typedef struct Boss01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x998];
} Boss01; // size = 0xADC

extern const ActorInit Boss_01_InitVars;

#endif

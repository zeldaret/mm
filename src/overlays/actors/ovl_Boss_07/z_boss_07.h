#ifndef Z_BOSS_07_H
#define Z_BOSS_07_H

#include "global.h"

struct Boss07;

typedef struct Boss07 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0xAADC];
} Boss07; // size = 0xAC20

extern const ActorInit Boss_07_InitVars;

#endif // Z_BOSS_07_H

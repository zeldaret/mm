#ifndef Z_BOSS_06_H
#define Z_BOSS_06_H

#include <global.h>

struct Boss06;

typedef struct Boss06 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8EC];
} Boss06; // size = 0xA30

extern const ActorInit Boss_06_InitVars;

#endif // Z_BOSS_06_H

#ifndef Z_EN_DEATH_H
#define Z_EN_DEATH_H

#include <global.h>

struct EnDeath;

typedef struct EnDeath {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x7F4];
} EnDeath; // size = 0x938

extern const ActorInit En_Death_InitVars;

#endif // Z_EN_DEATH_H

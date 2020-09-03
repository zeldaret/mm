#ifndef _Z_EN_DEATH_H_
#define _Z_EN_DEATH_H_

#include <global.h>

struct EnDeath;

typedef struct EnDeath {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x7F4];
} EnDeath; // size = 0x938

extern const ActorInit En_Death_InitVars;

#endif

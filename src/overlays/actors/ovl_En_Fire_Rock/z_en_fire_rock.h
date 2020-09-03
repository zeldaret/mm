#ifndef _Z_EN_FIRE_ROCK_H_
#define _Z_EN_FIRE_ROCK_H_

#include <global.h>

struct EnFireRock;

typedef struct EnFireRock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x94];
} EnFireRock; // size = 0x1D8

extern const ActorInit En_Fire_Rock_InitVars;

#endif

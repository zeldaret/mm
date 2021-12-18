#ifndef Z_EN_FISH_H
#define Z_EN_FISH_H

#include "global.h"

struct EnFish;

typedef struct EnFish {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk144[0x133];
    /* 0x277 */ s8 unk_277;
    /* 0x278 */ char unk278[0x4];
} EnFish; // size = 0x27C

extern const ActorInit En_Fish_InitVars;

#endif // Z_EN_FISH_H

#ifndef Z_EN_FISH_H
#define Z_EN_FISH_H

#include "global.h"

struct EnFish;

typedef struct EnFish {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk144[0x130];
    /* 0x274 */ s16 unk_274;
    /* 0x276 */ u8 unk_276;
    /* 0x278 */ char unk277[5];
} EnFish; // size = 0x27C

extern const ActorInit En_Fish_InitVars;

#endif // Z_EN_FISH_H

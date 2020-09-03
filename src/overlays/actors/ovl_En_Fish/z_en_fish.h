#ifndef _Z_EN_FISH_H_
#define _Z_EN_FISH_H_

#include <global.h>

struct EnFish;

typedef struct EnFish {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x138];
} EnFish; // size = 0x27C

extern const ActorInit En_Fish_InitVars;

#endif

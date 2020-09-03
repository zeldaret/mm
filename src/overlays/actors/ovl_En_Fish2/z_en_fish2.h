#ifndef _Z_EN_FISH2_H_
#define _Z_EN_FISH2_H_

#include <global.h>

struct EnFish2;

typedef struct EnFish2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x1ED4];
} EnFish2; // size = 0x2018

extern const ActorInit En_Fish2_InitVars;

#endif

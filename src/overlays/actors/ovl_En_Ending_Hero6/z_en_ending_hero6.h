#ifndef Z_EN_ENDING_HERO6_H
#define Z_EN_ENDING_HERO6_H

#include "global.h"

struct EnEndingHero6;

typedef struct EnEndingHero6 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x150];
} EnEndingHero6; // size = 0x294

extern const ActorInit En_Ending_Hero6_InitVars;

#endif // Z_EN_ENDING_HERO6_H

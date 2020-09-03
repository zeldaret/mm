#ifndef Z_EN_ENDING_HERO5_H
#define Z_EN_ENDING_HERO5_H

#include <global.h>

struct EnEndingHero5;

typedef struct EnEndingHero5 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x11C];
} EnEndingHero5; // size = 0x260

extern const ActorInit En_Ending_Hero5_InitVars;

#endif // Z_EN_ENDING_HERO5_H

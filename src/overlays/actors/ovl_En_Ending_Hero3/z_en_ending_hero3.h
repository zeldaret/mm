#ifndef _Z_EN_ENDING_HERO3_H_
#define _Z_EN_ENDING_HERO3_H_

#include <global.h>

struct EnEndingHero3;

typedef struct EnEndingHero3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x118];
} EnEndingHero3; // size = 0x25C

extern const ActorInit En_Ending_Hero3_InitVars;

#endif

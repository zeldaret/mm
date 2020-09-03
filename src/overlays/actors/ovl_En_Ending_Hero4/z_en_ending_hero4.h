#ifndef _Z_EN_ENDING_HERO4_H_
#define _Z_EN_ENDING_HERO4_H_

#include <global.h>

struct EnEndingHero4;

typedef struct EnEndingHero4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x118];
} EnEndingHero4; // size = 0x25C

extern const ActorInit En_Ending_Hero4_InitVars;

#endif

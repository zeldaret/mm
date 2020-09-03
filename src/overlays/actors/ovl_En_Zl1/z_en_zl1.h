#ifndef _Z_EN_ZL1_H_
#define _Z_EN_ZL1_H_

#include <global.h>

struct EnZl1;

typedef struct EnZl1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC0];
} EnZl1; // size = 0x204

extern const ActorInit En_Zl1_InitVars;

#endif

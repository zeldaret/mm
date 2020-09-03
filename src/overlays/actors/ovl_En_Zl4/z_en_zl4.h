#ifndef _Z_EN_ZL4_H_
#define _Z_EN_ZL4_H_

#include <global.h>

struct EnZl4;

typedef struct EnZl4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1B0];
} EnZl4; // size = 0x2F4

extern const ActorInit En_Zl4_InitVars;

#endif

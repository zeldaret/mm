#ifndef _Z_EN_BOJ_02_H_
#define _Z_EN_BOJ_02_H_

#include <global.h>

struct EnBoj02;

typedef struct EnBoj02 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4D8];
} EnBoj02; // size = 0x61C

extern const ActorInit En_Boj_02_InitVars;

#endif

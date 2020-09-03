#ifndef _Z_EN_BOJ_04_H_
#define _Z_EN_BOJ_04_H_

#include <global.h>

struct EnBoj04;

typedef struct EnBoj04 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4D8];
} EnBoj04; // size = 0x61C

extern const ActorInit En_Boj_04_InitVars;

#endif

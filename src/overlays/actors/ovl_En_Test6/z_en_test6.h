#ifndef _Z_EN_TEST6_H_
#define _Z_EN_TEST6_H_

#include <global.h>

struct EnTest6;

typedef struct EnTest6 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x144];
} EnTest6; // size = 0x288

extern const ActorInit En_Test6_InitVars;

#endif

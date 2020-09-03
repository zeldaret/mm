#ifndef _Z_EN_TEST4_H_
#define _Z_EN_TEST4_H_

#include <global.h>

struct EnTest4;

typedef struct EnTest4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x10];
} EnTest4; // size = 0x154

extern const ActorInit En_Test4_InitVars;

#endif

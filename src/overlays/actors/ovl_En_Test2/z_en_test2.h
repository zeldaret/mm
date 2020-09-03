#ifndef _Z_EN_TEST2_H_
#define _Z_EN_TEST2_H_

#include <global.h>

struct EnTest2;

typedef struct EnTest2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x4];
} EnTest2; // size = 0x148

extern const ActorInit En_Test2_InitVars;

#endif

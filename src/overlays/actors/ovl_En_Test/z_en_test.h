#ifndef _Z_EN_TEST_H_
#define _Z_EN_TEST_H_

#include <global.h>

struct EnTest;

typedef struct EnTest {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x578];
} EnTest; // size = 0x6BC

extern const ActorInit En_Test_InitVars;

#endif

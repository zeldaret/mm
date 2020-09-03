#ifndef _Z_EN_TEST5_H_
#define _Z_EN_TEST5_H_

#include <global.h>

struct EnTest5;

typedef struct EnTest5 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
} EnTest5; // size = 0x15C

extern const ActorInit En_Test5_InitVars;

#endif

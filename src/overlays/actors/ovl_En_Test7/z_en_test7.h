#ifndef _Z_EN_TEST7_H_
#define _Z_EN_TEST7_H_

#include <global.h>

struct EnTest7;

typedef struct EnTest7 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_0144[0x1D58];
} EnTest7; // size = 0x1E9C

extern const ActorInit En_Test7_InitVars;

#endif

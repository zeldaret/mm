#ifndef _Z_EN_GE1_H_
#define _Z_EN_GE1_H_

#include <global.h>

struct EnGe1;

typedef struct EnGe1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x188];
} EnGe1; // size = 0x2CC

extern const ActorInit En_Ge1_InitVars;

#endif

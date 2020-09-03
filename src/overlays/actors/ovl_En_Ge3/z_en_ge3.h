#ifndef _Z_EN_GE3_H_
#define _Z_EN_GE3_H_

#include <global.h>

struct EnGe3;

typedef struct EnGe3 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1DC];
} EnGe3; // size = 0x320

extern const ActorInit En_Ge3_InitVars;

#endif

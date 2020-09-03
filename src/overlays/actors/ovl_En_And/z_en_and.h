#ifndef _Z_EN_AND_H_
#define _Z_EN_AND_H_

#include <global.h>

struct EnAnd;

typedef struct EnAnd {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D0];
} EnAnd; // size = 0x314

extern const ActorInit En_And_InitVars;

#endif

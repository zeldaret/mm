#ifndef _Z_EN_BAGUO_H_
#define _Z_EN_BAGUO_H_

#include <global.h>

struct EnBaguo;

typedef struct EnBaguo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x788];
} EnBaguo; // size = 0x8CC

extern const ActorInit En_Baguo_InitVars;

#endif

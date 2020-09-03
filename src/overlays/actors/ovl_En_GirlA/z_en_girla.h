#ifndef _Z_EN_GIRLA_H_
#define _Z_EN_GIRLA_H_

#include <global.h>

struct EnGirlA;

typedef struct EnGirlA {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x88];
} EnGirlA; // size = 0x1CC

extern const ActorInit En_GirlA_InitVars;

#endif

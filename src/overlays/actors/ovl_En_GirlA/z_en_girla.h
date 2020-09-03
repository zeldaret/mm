#ifndef Z_EN_GIRLA_H
#define Z_EN_GIRLA_H

#include <global.h>

struct EnGirlA;

typedef struct EnGirlA {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x88];
} EnGirlA; // size = 0x1CC

extern const ActorInit En_GirlA_InitVars;

#endif // Z_EN_GIRLA_H

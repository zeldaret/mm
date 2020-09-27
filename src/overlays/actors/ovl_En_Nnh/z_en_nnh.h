#ifndef Z_EN_NNH_H
#define Z_EN_NNH_H

#include <global.h>

struct EnNnh;

typedef struct EnNnh {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x50];
} EnNnh; // size = 0x194

extern const ActorInit D_80C089E0;

#endif // Z_EN_NNH_H

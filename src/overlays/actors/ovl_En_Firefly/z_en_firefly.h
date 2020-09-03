#ifndef Z_EN_FIREFLY_H
#define Z_EN_FIREFLY_H

#include <global.h>

struct EnFirefly;

typedef struct EnFirefly {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x230];
} EnFirefly; // size = 0x374

extern const ActorInit En_Firefly_InitVars;

#endif // Z_EN_FIREFLY_H

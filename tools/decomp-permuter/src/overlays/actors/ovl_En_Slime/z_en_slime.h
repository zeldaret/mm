#ifndef Z_EN_SLIME_H
#define Z_EN_SLIME_H

#include <global.h>

struct EnSlime;

typedef struct EnSlime {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC4];
} EnSlime; // size = 0x208

extern const ActorInit En_Slime_InitVars;

#endif // Z_EN_SLIME_H

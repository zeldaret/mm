#ifndef Z_EN_DRAGON_H
#define Z_EN_DRAGON_H

#include <global.h>

struct EnDragon;

typedef struct EnDragon {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x3B8];
} EnDragon; // size = 0x4FC

extern const ActorInit En_Dragon_InitVars;

#endif // Z_EN_DRAGON_H

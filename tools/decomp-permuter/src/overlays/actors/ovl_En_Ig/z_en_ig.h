#ifndef Z_EN_IG_H
#define Z_EN_IG_H

#include <global.h>

struct EnIg;

typedef struct EnIg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2C8];
} EnIg; // size = 0x40C

extern const ActorInit En_Ig_InitVars;

#endif // Z_EN_IG_H

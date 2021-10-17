#ifndef Z_EN_GG2_H
#define Z_EN_GG2_H

#include <global.h>

struct EnGg2;

typedef struct EnGg2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1CC];
} EnGg2; // size = 0x310

extern const ActorInit En_Gg2_InitVars;

#endif // Z_EN_GG2_H

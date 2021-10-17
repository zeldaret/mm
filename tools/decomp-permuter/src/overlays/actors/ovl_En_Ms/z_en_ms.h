#ifndef Z_EN_MS_H
#define Z_EN_MS_H

#include <global.h>

struct EnMs;

typedef struct EnMs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x100];
} EnMs; // size = 0x244

extern const ActorInit En_Ms_InitVars;

#endif // Z_EN_MS_H

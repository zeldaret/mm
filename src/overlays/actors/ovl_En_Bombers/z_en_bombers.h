#ifndef Z_EN_BOMBERS_H
#define Z_EN_BOMBERS_H

#include <global.h>

struct EnBombers;

typedef struct EnBombers {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1D0];
} EnBombers; // size = 0x314

extern const ActorInit En_Bombers_InitVars;

#endif // Z_EN_BOMBERS_H

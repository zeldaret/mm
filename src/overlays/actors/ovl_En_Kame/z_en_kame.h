#ifndef Z_EN_KAME_H
#define Z_EN_KAME_H

#include <global.h>

struct EnKame;

typedef struct EnKame {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x248];
} EnKame; // size = 0x38C

extern const ActorInit En_Kame_InitVars;

#endif // Z_EN_KAME_H

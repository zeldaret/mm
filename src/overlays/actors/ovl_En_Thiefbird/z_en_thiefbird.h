#ifndef Z_EN_THIEFBIRD_H
#define Z_EN_THIEFBIRD_H

#include "global.h"

struct EnThiefbird;

typedef struct EnThiefbird {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x84C];
} EnThiefbird; // size = 0x990

extern const ActorInit En_Thiefbird_InitVars;

#endif // Z_EN_THIEFBIRD_H

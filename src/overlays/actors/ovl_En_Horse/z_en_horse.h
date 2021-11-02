#ifndef Z_EN_HORSE_H
#define Z_EN_HORSE_H

#include "global.h"
#include "z64skin.h"

struct EnHorse;

typedef struct EnHorse {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x00C];
    /* 0x150 */ s32 unk_150;
    /* 0x154 */ char unk_154[0x440];
} EnHorse; // size = 0x594

extern const ActorInit En_Horse_InitVars;

#endif // Z_EN_HORSE_H

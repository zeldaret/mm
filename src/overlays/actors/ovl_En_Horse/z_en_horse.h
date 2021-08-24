#ifndef Z_EN_HORSE_H
#define Z_EN_HORSE_H

#include "global.h"

struct EnHorse;

typedef struct EnHorse {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xA8];
    /* 0x1EC */ UNK_TYPE4 unk_1EC;
    /* 0x1F0 */ char unk_1F0[0x3A4];
} EnHorse; // size = 0x594

extern const ActorInit En_Horse_InitVars;

#endif // Z_EN_HORSE_H

#ifndef Z_BG_LOTUS_H
#define Z_BG_LOTUS_H

#include <global.h>

struct BgLotus;

typedef struct BgLotus {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x28];
} BgLotus; // size = 0x16C

extern const ActorInit Bg_Lotus_InitVars;

#endif // Z_BG_LOTUS_H

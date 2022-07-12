#ifndef Z_BG_HAKA_BOMBWALL_H
#define Z_BG_HAKA_BOMBWALL_H

#include "global.h"

struct BgHakaBombwall;

typedef void (*BgHakaBombwallActionFunc)(struct BgHakaBombwall*, PlayState*);

typedef struct BgHakaBombwall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x64];
    /* 0x1A8 */ BgHakaBombwallActionFunc actionFunc;
    /* 0x1AC */ char unk_1AC[0x4];
} BgHakaBombwall; // size = 0x1B0

extern const ActorInit Bg_Haka_Bombwall_InitVars;

#endif // Z_BG_HAKA_BOMBWALL_H

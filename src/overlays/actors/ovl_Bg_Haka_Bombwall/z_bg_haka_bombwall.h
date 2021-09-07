#ifndef Z_BG_HAKA_BOMBWALL_H
#define Z_BG_HAKA_BOMBWALL_H

#include "global.h"

struct BgHakaBombwall;

typedef void (*BgHakaBombwallActionFunc)(struct BgHakaBombwall*, GlobalContext*);

typedef struct BgHakaBombwall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x64];
    /* 0x01A8 */ BgHakaBombwallActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0x4];
} BgHakaBombwall; // size = 0x1B0

extern const ActorInit Bg_Haka_Bombwall_InitVars;

#endif // Z_BG_HAKA_BOMBWALL_H

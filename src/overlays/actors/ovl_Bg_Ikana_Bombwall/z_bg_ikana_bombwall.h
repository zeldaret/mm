#ifndef Z_BG_IKANA_BOMBWALL_H
#define Z_BG_IKANA_BOMBWALL_H

#include "global.h"

struct BgIkanaBombwall;

typedef void (*BgIkanaBombwallActionFunc)(struct BgIkanaBombwall*, GlobalContext*);

typedef struct BgIkanaBombwall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x64];
    /* 0x01A8 */ BgIkanaBombwallActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0x4];
} BgIkanaBombwall; // size = 0x1B0

extern const ActorInit Bg_Ikana_Bombwall_InitVars;

#endif // Z_BG_IKANA_BOMBWALL_H

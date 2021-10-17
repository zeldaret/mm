#ifndef Z_BG_IKANA_BOMBWALL_H
#define Z_BG_IKANA_BOMBWALL_H

#include <global.h>

struct BgIkanaBombwall;

typedef struct BgIkanaBombwall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} BgIkanaBombwall; // size = 0x1B0

extern const ActorInit Bg_Ikana_Bombwall_InitVars;

#endif // Z_BG_IKANA_BOMBWALL_H

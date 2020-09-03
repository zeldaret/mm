#ifndef _Z_BG_HAKA_BOMBWALL_H_
#define _Z_BG_HAKA_BOMBWALL_H_

#include <global.h>

struct BgHakaBombwall;

typedef struct BgHakaBombwall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} BgHakaBombwall; // size = 0x1B0

extern const ActorInit Bg_Haka_Bombwall_InitVars;

#endif

#ifndef _Z_BG_ASTR_BOMBWALL_H_
#define _Z_BG_ASTR_BOMBWALL_H_

#include <global.h>

struct BgAstrBombwall;

typedef struct BgAstrBombwall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xF8];
} BgAstrBombwall; // size = 0x23C

extern const ActorInit Bg_Astr_Bombwall_InitVars;

#endif

#ifndef _Z_BG_HAKUGIN_BOMBWALL_H_
#define _Z_BG_HAKUGIN_BOMBWALL_H_

#include <global.h>

struct BgHakuginBombwall;

typedef struct BgHakuginBombwall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} BgHakuginBombwall; // size = 0x1B0

extern const ActorInit Bg_Hakugin_Bombwall_InitVars;

#endif

#ifndef Z_BG_HAKUGIN_BOMBWALL_H
#define Z_BG_HAKUGIN_BOMBWALL_H

#include <global.h>

struct BgHakuginBombwall;

typedef struct BgHakuginBombwall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} BgHakuginBombwall; // size = 0x1B0

extern const ActorInit Bg_Hakugin_Bombwall_InitVars;

#endif // Z_BG_HAKUGIN_BOMBWALL_H

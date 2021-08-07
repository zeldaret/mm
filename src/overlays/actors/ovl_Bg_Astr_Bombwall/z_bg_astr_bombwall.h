#ifndef Z_BG_ASTR_BOMBWALL_H
#define Z_BG_ASTR_BOMBWALL_H

#include "global.h"

struct BgAstrBombwall;

typedef void (*BgAstrBombwallActionFunc)(struct BgAstrBombwall* this, GlobalContext* globalCtx);

typedef struct BgAstrBombwall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgAstrBombwallActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0xDC];
} BgAstrBombwall; // size = 0x23C

extern const ActorInit Bg_Astr_Bombwall_InitVars;

#endif // Z_BG_ASTR_BOMBWALL_H

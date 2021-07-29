#ifndef Z_BG_HAKUGIN_BOMBWALL_H
#define Z_BG_HAKUGIN_BOMBWALL_H

#include "global.h"

struct BgHakuginBombwall;

typedef void (*BgHakuginBombwallActionFunc)(struct BgHakuginBombwall* this, GlobalContext* globalCtx);

typedef struct BgHakuginBombwall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x64];
    /* 0x01A8 */ BgHakuginBombwallActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0x4];
} BgHakuginBombwall; // size = 0x1B0

extern const ActorInit Bg_Hakugin_Bombwall_InitVars;

#endif // Z_BG_HAKUGIN_BOMBWALL_H

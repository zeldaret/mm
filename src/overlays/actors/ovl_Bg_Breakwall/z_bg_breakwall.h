#ifndef Z_BG_BREAKWALL_H
#define Z_BG_BREAKWALL_H

#include "global.h"

struct BgBreakwall;

typedef void (*BgBreakwallActionFunc)(struct BgBreakwall* this, GlobalContext* globalCtx);

typedef struct BgBreakwall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C];
    /* 0x0160 */ BgBreakwallActionFunc actionFunc;
} BgBreakwall; // size = 0x164

extern const ActorInit Bg_Breakwall_InitVars;

#endif // Z_BG_BREAKWALL_H

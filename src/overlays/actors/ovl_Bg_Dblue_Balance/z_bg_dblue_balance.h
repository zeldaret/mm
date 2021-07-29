#ifndef Z_BG_DBLUE_BALANCE_H
#define Z_BG_DBLUE_BALANCE_H

#include "global.h"

struct BgDblueBalance;

typedef void (*BgDblueBalanceActionFunc)(struct BgDblueBalance* this, GlobalContext* globalCtx);

typedef struct BgDblueBalance {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x24];
    /* 0x0168 */ BgDblueBalanceActionFunc actionFunc;
    /* 0x016C */ char unk_16C[0xC0];
} BgDblueBalance; // size = 0x22C

extern const ActorInit Bg_Dblue_Balance_InitVars;

#endif // Z_BG_DBLUE_BALANCE_H

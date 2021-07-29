#ifndef Z_BG_GORON_OYU_H
#define Z_BG_GORON_OYU_H

#include "global.h"

struct BgGoronOyu;

typedef void (*BgGoronOyuActionFunc)(struct BgGoronOyu* this, GlobalContext* globalCtx);

typedef struct BgGoronOyu {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgGoronOyuActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x20];
} BgGoronOyu; // size = 0x180

extern const ActorInit Bg_Goron_Oyu_InitVars;

#endif // Z_BG_GORON_OYU_H

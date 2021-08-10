#ifndef Z_BG_IKANA_DHARMA_H
#define Z_BG_IKANA_DHARMA_H

#include "global.h"

struct BgIkanaDharma;

typedef void (*BgIkanaDharmaActionFunc)(struct BgIkanaDharma* this, GlobalContext* globalCtx);

typedef struct BgIkanaDharma {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x64];
    /* 0x01A8 */ BgIkanaDharmaActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0x4];
} BgIkanaDharma; // size = 0x1B0

extern const ActorInit Bg_Ikana_Dharma_InitVars;

#endif // Z_BG_IKANA_DHARMA_H

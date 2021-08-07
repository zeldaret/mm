#ifndef Z_BG_KEIKOKU_SAKU_H
#define Z_BG_KEIKOKU_SAKU_H

#include "global.h"

struct BgKeikokuSaku;

typedef void (*BgKeikokuSakuActionFunc)(struct BgKeikokuSaku* this, GlobalContext* globalCtx);

typedef struct BgKeikokuSaku {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgKeikokuSakuActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x4];
} BgKeikokuSaku; // size = 0x164

extern const ActorInit Bg_Keikoku_Saku_InitVars;

#endif // Z_BG_KEIKOKU_SAKU_H

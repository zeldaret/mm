#ifndef Z_BG_F40_FLIFT_H
#define Z_BG_F40_FLIFT_H

#include "global.h"

struct BgF40Flift;

typedef void (*BgF40FliftActionFunc)(struct BgF40Flift* this, GlobalContext* globalCtx);

typedef struct BgF40Flift {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgF40FliftActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x4];
} BgF40Flift; // size = 0x164

extern const ActorInit Bg_F40_Flift_InitVars;

#endif // Z_BG_F40_FLIFT_H

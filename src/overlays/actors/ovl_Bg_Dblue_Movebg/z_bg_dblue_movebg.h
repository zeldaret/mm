#ifndef Z_BG_DBLUE_MOVEBG_H
#define Z_BG_DBLUE_MOVEBG_H

#include "global.h"

struct BgDblueMovebg;

typedef void (*BgDblueMovebgActionFunc)(struct BgDblueMovebg* this, GlobalContext* globalCtx);

typedef struct BgDblueMovebg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgDblueMovebgActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x210];
} BgDblueMovebg; // size = 0x370

extern const ActorInit Bg_Dblue_Movebg_InitVars;

#endif // Z_BG_DBLUE_MOVEBG_H

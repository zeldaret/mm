#ifndef Z_BG_DANPEI_MOVEBG_H
#define Z_BG_DANPEI_MOVEBG_H

#include "global.h"

struct BgDanpeiMovebg;

typedef void (*BgDanpeiMovebgActionFunc)(struct BgDanpeiMovebg* this, GlobalContext* globalCtx);

typedef struct BgDanpeiMovebg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgDanpeiMovebgActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x78];
} BgDanpeiMovebg; // size = 0x1D8

extern const ActorInit Bg_Danpei_Movebg_InitVars;

#endif // Z_BG_DANPEI_MOVEBG_H

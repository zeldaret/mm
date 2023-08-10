#ifndef Z_BG_DANPEI_MOVEBG_H
#define Z_BG_DANPEI_MOVEBG_H

#include "global.h"

struct BgDanpeiMovebg;

typedef void (*BgDanpeiMovebgActionFunc)(struct BgDanpeiMovebg*, PlayState*);

typedef struct BgDanpeiMovebg {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgDanpeiMovebgActionFunc actionFunc;
    /* 0x160 */ ActorPathing actorPath;
    /* 0x1CC */ u16 unk_1CC;
    /* 0x1CE */ u16 unk_1CE;
    /* 0x1D0 */ Gfx* unk_1D0;
    /* 0x1D4 */ s8 bankIdx;
} BgDanpeiMovebg; // size = 0x1D8

#endif // Z_BG_DANPEI_MOVEBG_H

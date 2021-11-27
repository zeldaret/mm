#ifndef Z_BG_DANPEI_MOVEBG_H
#define Z_BG_DANPEI_MOVEBG_H

#include "global.h"

struct BgDanpeiMovebg;

typedef void (*BgDanpeiMovebgActionFunc)(struct BgDanpeiMovebg*, GlobalContext*);

typedef struct BgDanpeiMovebg {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ BgDanpeiMovebgActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x6C];
    /* 0x01CC */ u16 unk_1CC;
    /* 0x01CE */ char unk_1CE[0xA];
} BgDanpeiMovebg; // size = 0x1D8

extern const ActorInit Bg_Danpei_Movebg_InitVars;

#endif // Z_BG_DANPEI_MOVEBG_H

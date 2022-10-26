#ifndef Z_BG_TOBIRA01_H
#define Z_BG_TOBIRA01_H

#include "global.h"

struct BgTobira01;

typedef void (*BgTobira01ActionFunc)(struct BgTobira01* this, PlayState* play);

typedef struct BgTobira01 {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgTobira01ActionFunc actionFunc;
    /* 0x160 */ s16 unk_160;
    /* 0x162 */ s16 unk_162;
    /* 0x164 */ f32 unk_164;
    /* 0x168 */ s32 unk_168;
    /* 0x16C */ s32 unk_16C;
} BgTobira01; // size = 0x170

#endif // Z_BG_TOBIRA01_H

#ifndef Z_BG_TOBIRA01_H
#define Z_BG_TOBIRA01_H

#include "global.h"

struct BgTobira01;

typedef void (*updateFunc)(struct BgTobira01*, PlayState*);

typedef struct BgTobira01 {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ updateFunc unk15C;
    /* 0x160 */ s16 unk160;
    /* 0x162 */ s16 unk162;
    /* 0x164 */ f32 unk164;
    /* 0x168 */ s32 unk168;
    /* 0x16C */ s32 unk16C;
} BgTobira01; // size = 0x170

#endif // Z_BG_TOBIRA01_H

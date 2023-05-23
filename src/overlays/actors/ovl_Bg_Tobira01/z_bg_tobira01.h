#ifndef Z_BG_TOBIRA01_H
#define Z_BG_TOBIRA01_H

#include "global.h"

struct BgTobira01;

typedef void (*TobiraActionFunction)(struct BgTobira01*, PlayState*);

typedef struct BgTobira01 {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ TobiraActionFunction actionFunction;
    /* 0x160 */ s16 doorYPositionTick;
    /* 0x162 */ s16 isNight;
    /* 0x164 */ f32 yPosition;
    /* 0x168 */ s32 cutscenePlayed;
    /* 0x16C */ s32 unk16C;
} BgTobira01; // size = 0x170


#endif // Z_BG_TOBIRA01_H

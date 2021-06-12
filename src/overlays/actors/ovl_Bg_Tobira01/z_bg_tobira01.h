#ifndef Z_BG_TOBIRA01_H
#define Z_BG_TOBIRA01_H

#include <global.h>

struct BgTobira01;

typedef void (*BgTobira01ActionFunc)(struct BgTobira01*, struct GlobalContext*);

typedef struct BgTobira01 {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgTobira01ActionFunc actionFunc;
    /* 0x160 */ s16 timer;
    /* 0x162 */ s16 timer2;
    /* 0x164 */ f32 yOffset;
    /* 0x168 */ s32 playCutscene;
    /* 0x16C */ s32 unk_16C; // unused besides being set to 0
} BgTobira01; // size = 0x170

extern const ActorInit Bg_Tobira01_InitVars;

#endif // Z_BG_TOBIRA01_H

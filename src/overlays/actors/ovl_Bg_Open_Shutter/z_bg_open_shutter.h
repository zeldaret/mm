#ifndef Z_BG_OPEN_SHUTTER_H
#define Z_BG_OPEN_SHUTTER_H

#include "global.h"

#define BGOPENSHUTTER_GET_A(thisx) ((u16)((thisx)->params) >> 0xA)

struct BgOpenShutter;

typedef void (*BgOpenShutterActionFunc)(struct BgOpenShutter*, PlayState*);

typedef struct BgOpenShutter {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ s16 unk_15C;
    /* 0x160 */ BgOpenShutterActionFunc actionFunc;
    /* 0x164 */ s32 unk_164;
} BgOpenShutter; // size = 0x168

extern const ActorInit Bg_Open_Shutter_InitVars;

#endif // Z_BG_OPEN_SHUTTER_H

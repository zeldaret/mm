#ifndef Z_BG_IKANA_DHARMA_H
#define Z_BG_IKANA_DHARMA_H

#include "global.h"

#define BGIKANADHARMA_GET_SWITCHFLAG(thisx) (((thisx)->params >> 8) & 0x7F)

struct BgIkanaDharma;

typedef void (*BgIkanaDharmaActionFunc)(struct BgIkanaDharma*, GlobalContext*);

typedef struct BgIkanaDharma {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderCylinder unk15C;
    /* 0x01A8 */ BgIkanaDharmaActionFunc actionFunc;
    /* 0x01AC */ s8 unk_1AC;
} BgIkanaDharma; // size = 0x1B0

extern const ActorInit Bg_Ikana_Dharma_InitVars;

#endif // Z_BG_IKANA_DHARMA_H

#ifndef Z_BG_DBLUE_WATERFALL_H
#define Z_BG_DBLUE_WATERFALL_H

#include "global.h"

struct BgDblueWaterfall;

typedef void (*BgDblueWaterfallActionFunc)(struct BgDblueWaterfall*, GlobalContext*);

#define BGDBLUEWATERFALL_GET_7F(thisx) ((thisx)->params & 0x7F)
#define BGDBLUEWATERFALL_GET_100(thisx) (((thisx)->params >> 8) & 1)

typedef struct BgDblueWaterfall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ AnimatedMaterial* unk_190;
    /* 0x0194 */ BgDblueWaterfallActionFunc actionFunc;
    /* 0x0198 */ f32 unk_198;
    /* 0x019C */ s16 unk_19C;
    /* 0x019E */ u8 unk_19E;
    /* 0x019F */ u8 unk_19F;
    /* 0x01A0 */ u8 unk_1A0;
    /* 0x01A1 */ UNK_TYPE1 unk1A1[2];
    /* 0x01A3 */ s8 unk_1A3;
    /* 0x01A4 */ s16 unk_1A4;
    /* 0x01A6 */ UNK_TYPE1 unk1A6[1];
    /* 0x01A7 */ s8 unk_1A7;
    /* 0x01A8 */ f32 unk_1A8;
} BgDblueWaterfall; // size = 0x1AC

extern const ActorInit Bg_Dblue_Waterfall_InitVars;

#endif // Z_BG_DBLUE_WATERFALL_H

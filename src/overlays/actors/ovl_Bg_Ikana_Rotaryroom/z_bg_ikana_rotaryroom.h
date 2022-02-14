#ifndef Z_BG_IKANA_ROTARYROOM_H
#define Z_BG_IKANA_ROTARYROOM_H

#include "global.h"

struct BgIkanaRotaryroom;

typedef void (*BgIkanaRotaryroomActionFunc)(struct BgIkanaRotaryroom*, GlobalContext*);
typedef void (*BgIkanaRotaryroomUnkFunc)(Actor*, GlobalContext*);
typedef void (*BgIkanaRotaryroomUnkFunc2)(struct BgIkanaRotaryroom*, GlobalContext*);

#define BGIKANAROTARYROOM_GET_1(thisx) ((thisx)->params & 1)
#define BGIKANAROTARYROOM_GET_FE(thisx) (((thisx)->params >> 1) & 0x7F)
#define BGIKANAROTARYROOM_GET_7F00(thisx) (((thisx)->params >> 8) & 0x7F)

typedef struct {
    /* 0x00 */ Actor* unk_00;
    /* 0x04 */ MtxF unk_04;
} BgIkanaRotaryroomStruct1; // size = 0x44

typedef struct {
    /* 0x00 */ Actor* unk_00;
    /* 0x04 */ MtxF unk_04;
    /* 0x44 */ Vec3s unk_44;
    /* 0x4C */ f32 unk_4C;
} BgIkanaRotaryroomStruct2; // size = 0x50

typedef struct {
    /* 0x00 */ MtxF unk_00;
    /* 0x40 */ Vec3s unk_40;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ Vec3f unk_4C;
} BgIkanaRotaryroomStruct3; // size = 0x58

typedef struct BgIkanaRotaryroom {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ ColliderJntSph collider;
    /* 0x017C */ ColliderJntSphElement colliderElements[2];
    /* 0x01FC */ AnimatedMaterial* unk_1FC;
    /* 0x0200 */ BgIkanaRotaryroomUnkFunc unk_200;
    /* 0x0204 */ BgIkanaRotaryroomStruct1 unk_204;
    /* 0x0248 */ BgIkanaRotaryroomStruct1 unk_248[2];
    /* 0x02D0 */ BgIkanaRotaryroomStruct1 unk_2D0[4];
    /* 0x03E0 */ BgIkanaRotaryroomStruct2 unk_3E0[4];
    /* 0x0520 */ BgIkanaRotaryroomStruct3 unk_520;
    /* 0x0578 */ BgIkanaRotaryroomUnkFunc2 unk_578;
    /* 0x057C */ BgIkanaRotaryroomUnkFunc2 unk_57C;
    /* 0x0580 */ BgIkanaRotaryroomActionFunc actionFunc;
    /* 0x0584 */ s16 unk_584;
} BgIkanaRotaryroom; // size = 0x588

extern const ActorInit Bg_Ikana_Rotaryroom_InitVars;

#endif // Z_BG_IKANA_ROTARYROOM_H

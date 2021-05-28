#ifndef Z_EN_MA_YTO_H
#define Z_EN_MA_YTO_H

#include <global.h>
#include "overlays/actors/ovl_En_Ma_Yts/z_en_ma_yts.h"

struct EnMaYto;

typedef void (*EnMaYtoActionFunc)(struct EnMaYto*, GlobalContext*);

typedef struct EnMaYto {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnMaYtoActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ char unk_1D8[0x8];
    /* 0x1E0 */ Vec3s unk_1E0;
    /* 0x1E6 */ Vec3s unk_1E6;
    /* 0x1F0 */ f32 unk_1EC;
    /* 0x1F0 */ Vec3f unk_1F0;
    /* 0x1FC */ char unk_1FC[0x4]; // unused
    /* 0x200 */ s32 unk_200;
    /* 0x204 */ s32 type;
    /* 0x208 */ Vec3s unk_208;
    /* 0x20E */ char unk_20E[0x2];
    /* 0x210 */ char unk_210[0x7C];
    /* 0x28C */ Vec3s unk_28C;
    /* 0x292 */ char unk_292[0x2];
    /* 0x294 */ char unk_294[0x7C];
    /* 0x310 */ s16 unk_310;
    /* 0x312 */ char unk_312[0x2]; // unused
    /* 0x314 */ s16 unk_314;
    /* 0x316 */ s16 overrideEyeTexIndex; // If non-zero, then this index will be used instead of eyeTexIndex
    /* 0x318 */ s16 mouthTexIndex;
    /* 0x31A */ s16 eyeTexIndex;
    /* 0x31C */ s16 blinkTimer;
    /* 0x31E */ s16 unk_31E;
    /* 0x320 */ s16 unk_320;
    /* 0x322 */ u16 textId;
} EnMaYto; // size = 0x324

extern const ActorInit En_Ma_Yto_InitVars;

typedef enum {
    /* 0 */ EN_NA_YTO_TYPE_0, // Strokes cow
    /* 1 */ EN_NA_YTO_TYPE_1, // Strokes cow siting
    /* 2 */ EN_NA_YTO_TYPE_2,
    /* 3 */ EN_NA_YTO_TYPE_3, // Cutscene
    /* 4 */ EN_NA_YTO_TYPE_4  // Credits?
} EnMaYtoType;

#define EN_MA_YTO_PARSE_TYPE(params) (((params)&0xF000) >> 12)
#define EN_MA_YTO_PARAM(enMaYtsType, arg1) (((enMaYtsType) << 12) | ((arg1) << 8))

/**
 * EN_NA_YTO_TYPE_0: 
 * EN_NA_YTO_TYPE_1: 
 * EN_NA_YTO_TYPE_2: 
 * EN_NA_YTO_TYPE_3: 
 * EN_NA_YTO_TYPE_4: 
 */

#endif // Z_EN_MA_YTO_H

#ifndef Z_EN_MA_YTO_H
#define Z_EN_MA_YTO_H

#include <global.h>
#include "overlays/actors/ovl_En_Ma_Yts/z_en_ma_yts.h"

struct EnMaYto;

typedef void (*EnMaYtoActionFunc)(struct EnMaYto*, GlobalContext*);

// Limbs of OBJECT_MA2
typedef enum {
    /* 00 */ MA2_LIMB_NONE,
    /* 01 */ MA2_LIMB_ROOT,

    /* 02 */ MA2_LIMB_TORSO,

    /* 03 */ MA2_LIMB_ARM_LEFT,
    /* 04 */ MA2_LIMB_FOREARM_LEFT,
    /* 05 */ MA2_LIMB_HAND_LEFT,

    /* 06 */ MA2_LIMB_ARM_RIGHT,
    /* 07 */ MA2_LIMB_FOREARM_RIGHT,
    /* 08 */ MA2_LIMB_HAND_RIGHT,

    /* 09 */ MA2_LIMB_HEAD,
    /* 10 */ MA2_LIMB_HAIR,

    /* 11 */ MA2_LIMB_PELVIS,

    /* 12 */ MA2_LIMB_TIGHT_LEFT,
    /* 13 */ MA2_LIMB_LEG_LEFT,
    /* 14 */ MA2_LIMB_FOOT_LEFT,

    /* 15 */ MA2_LIMB_TIGHT_RIGHT,
    /* 16 */ MA2_LIMB_LEG_RIGHT,
    /* 17 */ MA2_LIMB_FOOT_RIGHT,

    /* 18 */ MA2_LIMB_DRESS_0,
    /* 19 */ MA2_LIMB_DRESS_1,
    /* 20 */ MA2_LIMB_DRESS_2,
    /* 21 */ MA2_LIMB_DRESS_3,

    /* 22 */ MA2_LIMB_MAX
} ObjectMa2Limbs;


typedef struct EnMaYto {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnMaYtoActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ struct_800BD888_arg1 unk_1D8;
    /* 0x200 */ s32 unk_200;
    /* 0x204 */ s32 type;
    /* 0x208 */ Vec3s limbDrawTbl[MA2_LIMB_MAX];
    /* 0x28C */ Vec3s transitionDrawTbl[MA2_LIMB_MAX];
    /* 0x310 */ s16 unk_310; // state
    /* 0x312 */ char unk_312[0x2]; // unused
    /* 0x314 */ s16 unk_314; // currentAnim?
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
    /* 0 */ MA_YTO_TYPE_0, // Strokes cow on day 1
    /* 1 */ MA_YTO_TYPE_BARN, // Strokes cow siting. At barn
    /* 2 */ MA_YTO_TYPE_2, // Dinner, likely
    /* 3 */ MA_YTO_TYPE_AFTERMILKRUN, // After Milk Run minigame
    /* 4 */ MA_YTO_TYPE_4  // HugCutscene. 
} EnMaYtoType;

#define EN_MA_YTO_PARSE_TYPE(params) (((params)&0xF000) >> 12)
#define EN_MA_YTO_PARAM(enMaYtsType, arg1) (((enMaYtsType) << 12) | ((arg1) << 8))

/**
 * MA_YTO_TYPE_0: 
 * MA_YTO_TYPE_BARN: 
 * MA_YTO_TYPE_2: 
 * MA_YTO_TYPE_AFTERMILKRUN: 
 * MA_YTO_TYPE_4: 
 */

#endif // Z_EN_MA_YTO_H

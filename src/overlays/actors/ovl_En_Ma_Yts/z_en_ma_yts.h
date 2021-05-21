#ifndef Z_EN_MA_YTS_H
#define Z_EN_MA_YTS_H

#include <global.h>

struct EnMaYts;

typedef void (*EnMaYtsActionFunc)(struct EnMaYts*, GlobalContext*);

#define EN_MA_YTS_LIMB_TABLE_COUNT 23

typedef enum {
    /* 00 */ EN_MA_YTS_LIMB_00,
    /* 01 */ EN_MA_YTS_LIMB_PELVIS,
    /* 02 */ EN_MA_YTS_LIMB_TIGHT_LEFT,
    /* 03 */ EN_MA_YTS_LIMB_LEG_LEFT,
    /* 04 */ EN_MA_YTS_LIMB_FOOT_LEFT,
    /* 05 */ EN_MA_YTS_LIMB_TIGHT_RIGHT,
    /* 06 */ EN_MA_YTS_LIMB_LEG_RIGHT,
    /* 07 */ EN_MA_YTS_LIMB_FOOT_RIGHT,
    /* 08 */ EN_MA_YTS_LIMB_DRESS_0,
    /* 09 */ EN_MA_YTS_LIMB_DRESS_1,
    /* 10 */ EN_MA_YTS_LIMB_DRESS_2,
    /* 11 */ EN_MA_YTS_LIMB_DRESS_3,
    /* 12 */ EN_MA_YTS_LIMB_TORSO,
    /* 13 */ EN_MA_YTS_LIMB_HEAD,
    /* 14 */ EN_MA_YTS_LIMB_HAIR_TOP,
    /* 15 */ EN_MA_YTS_LIMB_HAIR_BOTTOM,
    /* 16 */ EN_MA_YTS_LIMB_ARM_LEFT,
    /* 17 */ EN_MA_YTS_LIMB_FOREARM_LEFT,
    /* 18 */ EN_MA_YTS_LIMB_HAND_LEFT,
    /* 19 */ EN_MA_YTS_LIMB_ARM_RIGHT,
    /* 20 */ EN_MA_YTS_LIMB_FOREARM_RIGHT,
    /* 21 */ EN_MA_YTS_LIMB_HAND_RIGHT
} EnMaYtsLimbs;

typedef struct EnMaYts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnMaYtsActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ struct_800BD888_arg1 unk_1D8;
    /* 0x200 */ s32 unk_200; // Set, but not used
    /* 0x204 */ Vec3s limbDrawTbl[EN_MA_YTS_LIMB_TABLE_COUNT];
    /* 0x28E */ char unk_28E[0x6];
    /* 0x294 */ Vec3s transitionDrawTbl[EN_MA_YTS_LIMB_TABLE_COUNT];
    /* 0x31E */ char unk_31E[0x8];
    /* 0x326 */ s16 blinkTimer;
    /* 0x328 */ s16 overrideEyeTexIndex; // If non-zero, then this index will be used instead of eyeTexIndex
    /* 0x32A */ s16 eyeTexIndex;
    /* 0x32C */ s16 unk_32C; // flag?
    /* 0x32E */ s16 mouthTexIndex;
    /* 0x330 */ s16 type;
    /* 0x332 */ char unk_332[0x2];
    /* 0x334 */ s16 unk_334;
    /* 0x336 */ s16 hasBow;
    /* 0x338 */ u16 textId;
    /* 0x33A */ char unk_33A[0x2];
} EnMaYts; // size = 0x33C

extern const ActorInit En_Ma_Yts_InitVars;

typedef enum {
    /* 0 */ EN_NA_YTS_TYPE_0,
    /* 1 */ EN_NA_YTS_TYPE_SITTING,
    /* 2 */ EN_NA_YTS_TYPE_SLEEPING,
    /* 3 */ EN_NA_YTS_TYPE_BOW // EN_NA_YTS_TYPE_CUTSCENE?
} EnMaYtsType;

#define EN_MA_YTS_PARAM(enMaYtsType) ((enMaYtsType) << 12)

#endif // Z_EN_MA_YTS_H

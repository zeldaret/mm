#ifndef Z_EN_MA_YTS_H
#define Z_EN_MA_YTS_H

#include "global.h"

struct EnMaYts;

typedef void (*EnMaYtsActionFunc)(struct EnMaYts*, GlobalContext*);

typedef enum {
    /* 00 */ MA1_LIMB_NONE,
    /* 01 */ MA1_LIMB_ROOT,
    /* 02 */ MA1_LIMB_PELVIS,
    /* 03 */ MA1_LIMB_TIGHT_LEFT,
    /* 04 */ MA1_LIMB_LEG_LEFT,
    /* 05 */ MA1_LIMB_FOOT_LEFT,
    /* 06 */ MA1_LIMB_TIGHT_RIGHT,
    /* 07 */ MA1_LIMB_LEG_RIGHT,
    /* 08 */ MA1_LIMB_FOOT_RIGHT,
    /* 09 */ MA1_LIMB_DRESS_0,
    /* 00 */ MA1_LIMB_DRESS_1,
    /* 11 */ MA1_LIMB_DRESS_2,
    /* 12 */ MA1_LIMB_DRESS_3,
    /* 13 */ MA1_LIMB_TORSO,
    /* 14 */ MA1_LIMB_HEAD,
    /* 15 */ MA1_LIMB_HAIR_TOP,
    /* 16 */ MA1_LIMB_HAIR_BOTTOM,
    /* 17 */ MA1_LIMB_ARM_LEFT,
    /* 18 */ MA1_LIMB_FOREARM_LEFT,
    /* 19 */ MA1_LIMB_HAND_LEFT,
    /* 20 */ MA1_LIMB_ARM_RIGHT,
    /* 21 */ MA1_LIMB_FOREARM_RIGHT,
    /* 22 */ MA1_LIMB_HAND_RIGHT,
    /* 23 */ MA1_LIMB_MAX
} ObjectMa1Limbs;

typedef struct EnMaYts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnMaYtsActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ struct_800BD888_arg1 unk_1D8;
    /* 0x200 */ s32 unk_200; // Set, but not used
    /* 0x204 */ Vec3s jointTable[MA1_LIMB_MAX];
    /* 0x28E */ char unk_28E[0x6];
    /* 0x294 */ Vec3s morphTable[MA1_LIMB_MAX];
    /* 0x31E */ char unk_31E[0x8];
    /* 0x326 */ s16 blinkTimer;
    /* 0x328 */ s16 overrideEyeTexIndex; // If non-zero, then this index will be used instead of eyeTexIndex
    /* 0x32A */ s16 eyeTexIndex;
    /* 0x32C */ s16 unk_32C; // flag?
    /* 0x32E */ s16 mouthTexIndex;
    /* 0x330 */ s16 type;
    /* 0x332 */ char unk_332[0x2];
    /* 0x334 */ s16 endCreditsFlag;
    /* 0x336 */ s16 hasBow;
    /* 0x338 */ u16 textId;
} EnMaYts; // size = 0x33C

extern const ActorInit En_Ma_Yts_InitVars;

typedef enum {
    /* 0 */ MA_YTS_TYPE_BARN,
    /* 1 */ MA_YTS_TYPE_SITTING,
    /* 2 */ MA_YTS_TYPE_SLEEPING,
    /* 3 */ MA_YTS_TYPE_ENDCREDITS
} EnMaYtsType;

#define EN_MA_YTS_PARSE_TYPE(actor) ((((actor)->params)&0xF000) >> 12)
#define EN_MA_YTS_PARAM(enMaYtsType) ((enMaYtsType) << 12)

/**
 * MA_YTS_TYPE_BARN: In the barn, accompanying Cremia. Cremia's actor will handle her dialogue if spoken to.
 * MA_YTS_TYPE_SITTING: Having dinner or looking after the ranch.
 * MA_YTS_TYPE_SLEEPING: Sleeping. Can be seen in the second night in her house if the player failed the alien invasion.
 * MA_YTS_TYPE_ENDCREDITS: Used in the end credits sequence.
 */

#endif // Z_EN_MA_YTS_H

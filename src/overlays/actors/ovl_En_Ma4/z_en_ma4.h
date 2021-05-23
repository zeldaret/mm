#ifndef Z_EN_MA4_H
#define Z_EN_MA4_H

#include <global.h>

struct EnMa4;

typedef void (*EnMa4ActionFunc)(struct EnMa4*, GlobalContext*);

// Limbs of OBJECT_MA1
#define OBJECT_MA1_LIMB_TABLE_COUNT 23
typedef enum {
    /* 00 */ OBJECT_MA1_LIMB_00,
    /* 01 */ OBJECT_MA1_LIMB_PELVIS,
    /* 02 */ OBJECT_MA1_LIMB_TIGHT_LEFT,
    /* 03 */ OBJECT_MA1_LIMB_LEG_LEFT,
    /* 04 */ OBJECT_MA1_LIMB_FOOT_LEFT,
    /* 05 */ OBJECT_MA1_LIMB_TIGHT_RIGHT,
    /* 06 */ OBJECT_MA1_LIMB_LEG_RIGHT,
    /* 07 */ OBJECT_MA1_LIMB_FOOT_RIGHT,
    /* 08 */ OBJECT_MA1_LIMB_DRESS_0,
    /* 09 */ OBJECT_MA1_LIMB_DRESS_1,
    /* 10 */ OBJECT_MA1_LIMB_DRESS_2,
    /* 11 */ OBJECT_MA1_LIMB_DRESS_3,
    /* 12 */ OBJECT_MA1_LIMB_TORSO,
    /* 13 */ OBJECT_MA1_LIMB_HEAD,
    /* 14 */ OBJECT_MA1_LIMB_HAIR_TOP,
    /* 15 */ OBJECT_MA1_LIMB_HAIR_BOTTOM,
    /* 16 */ OBJECT_MA1_LIMB_ARM_LEFT,
    /* 17 */ OBJECT_MA1_LIMB_FOREARM_LEFT,
    /* 18 */ OBJECT_MA1_LIMB_HAND_LEFT,
    /* 19 */ OBJECT_MA1_LIMB_ARM_RIGHT,
    /* 20 */ OBJECT_MA1_LIMB_FOREARM_RIGHT,
    /* 21 */ OBJECT_MA1_LIMB_HAND_RIGHT
} ObjectMa1Limbs;

typedef struct EnMa4 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnMa4ActionFunc actionFunc;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ u16 unk_1D8;
    /* 0x1DA */ char unk1DA[0x2];
    /* 0x1DC */ char unk1DC[0x4];
    /* 0x1E0 */ Vec3s unk_1E0;
    /* 0x1E6 */ Vec3s unk_1E6;
    /* 0x1EC */ char unk1EC[0x4];
    /* 0x1F0 */ Vec3f unk_1F0;
    /* 0x1FC */ char unk1FC[0x4];
    /* 0x200 */ Vec3s* unk_200;
    /* 0x204 */ Vec3s limbDrawTable[OBJECT_MA1_LIMB_TABLE_COUNT];
    /* 0x28E */ char unk28E[0x6];
    /* 0x294 */ Vec3s transitionDrawTable[OBJECT_MA1_LIMB_TABLE_COUNT];
    /* 0x31E */ char unk31E[0x6];
    /* 0x324 */ s16 unk_324;
    /* 0x326 */ s16 unk_326; // pathPointsCount
    /* 0x328 */ char unk_328[0x2]; // unused
    /* 0x32A */ s16 unk_32A; // blinkTimer
    /* 0x33C */ s16 unk_32C; // overrideEyeTexIndex
    /* 0x32E */ s16 unk_32E; // eyeTexIndex
    /* 0x330 */ s16 unk_330; // mouthTexIndex
    /* 0x332 */ s16 unk_332; // type?
    /* 0x334 */ u16 unk_334;
    /* 0x336 */ s16 unk_336;
    /* 0x338 */ s16 unk_338; // modified by EnPoFusen
    /* 0x33A */ s16 unk_33A;
    /* 0x33C */ s16 unk_33C;
    /* 0x33E */ u16 unk_33E;
} EnMa4; // size = 0x340

extern const ActorInit En_Ma4_InitVars;

#endif // Z_EN_MA4_H

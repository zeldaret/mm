#ifndef Z_EN_JG_H
#define Z_EN_JG_H

#include "global.h"

typedef enum {
    /*  0 */ EN_JG_LIMB_NONE,
    /*  1 */ EN_JG_LIMB_ROOT, // Root of Upper Body Root and Pelvis
    /*  2 */ EN_JG_LIMB_UPPER_BODY_ROOT, // Root of Lower Back and Upper Back
    /*  3 */ EN_JG_LIMB_LOWER_BACK,
    /*  4 */ EN_JG_LIMB_UPPER_BACK, // Root of Left Arm Root, Right Arm Root, and Neck
    /*  5 */ EN_JG_LIMB_LEFT_ARM_ROOT,
    /*  6 */ EN_JG_LIMB_LEFT_SHOULDER_AND_UPPER_ARM,
    /*  7 */ EN_JG_LIMB_LEFT_FOREARM,
    /*  8 */ EN_JG_LIMB_LEFT_WRIST, // Root of Left Hand and Thumb and Left Fingers
    /*  9 */ EN_JG_LIMB_LEFT_HAND_AND_THUMB,
    /* 10 */ EN_JG_LIMB_LEFT_FINGERS,
    /* 11 */ EN_JG_LIMB_RIGHT_ARM_ROOT,
    /* 12 */ EN_JG_LIMB_RIGHT_SHOULDER_AND_UPPER_ARM,
    /* 13 */ EN_JG_LIMB_RIGHT_FOREARM,
    /* 14 */ EN_JG_LIMB_RIGHT_WRIST,  // Root of Right Hand and Thumb and Right Fingers
    /* 15 */ EN_JG_LIMB_RIGHT_HAND_AND_THUMB,
    /* 16 */ EN_JG_LIMB_RIGHT_FINGERS,
    /* 17 */ EN_JG_LIMB_NECK, // Root of Left Hair End, Right Hair End, Hair Back, and Head
    /* 18 */ EN_JG_LIMB_LEFT_HAIR_END,
    /* 19 */ EN_JG_LIMB_RIGHT_HAIR_END,
    /* 20 */ EN_JG_LIMB_HAIR_BACK,
    /* 21 */ EN_JG_LIMB_HEAD,
    /* 22 */ EN_JG_LIMB_LOWER_LIP,
    /* 23 */ EN_JG_LIMB_BEARD_ROOT,
    /* 24 */ EN_JG_LIMB_UPPER_BEARD,
    /* 25 */ EN_JG_LIMB_LOWER_BEARD,
    /* 26 */ EN_JG_LIMB_PELVIS, // Root of Left Leg Root and Right Leg Root
    /* 27 */ EN_JG_LIMB_LEFT_LEG_ROOT,
    /* 28 */ EN_JG_LIMB_LEFT_THIGH,
    /* 29 */ EN_JG_LIMB_LEFT_SHIN,
    /* 30 */ EN_JG_LIMB_LEFT_FOOT,
    /* 31 */ EN_JG_LIMB_RIGHT_LEG_ROOT,
    /* 32 */ EN_JG_LIMB_RIGHT_THIGH,
    /* 33 */ EN_JG_LIMB_RIGHT_SHIN,
    /* 34 */ EN_JG_LIMB_RIGHT_FOOT,
    /* 35 */ EN_JG_LIMB_MAX,
} EnJgLimbs;

struct EnJg;

typedef void (*EnJgActionFunc)(struct EnJg*, GlobalContext*);

typedef struct EnJg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Actor* unk_144;
    /* 0x148 */ Actor* icePoly;
    /* 0x14C */ ColliderCylinder collider;
    /* 0x198 */ SkelAnime skelAnime;
    /* 0x1DC */ EnJgActionFunc actionFunc;
    /* 0x1E0 */ Path* path;
    /* 0x1E4 */ s32 unk_1E4;
    /* 0x1E8 */ Actor* drum;
    /* 0x1EC */ Vec3s unk_1EC;
    /* 0x1F2 */ Vec3s unk_1F2;
    /* 0x1F8 */ Vec3s jointTable[EN_JG_LIMB_MAX];
    /* 0x2CA */ Vec3s morphTable[EN_JG_LIMB_MAX];
    /* 0x39C */ s16 unk_39C;
    /* 0x39E */ s16 animationIndex;
    /* 0x3A0 */ s16 unk_3A0;
    /* 0x3A2 */ s16 unk_3A2;
    /* 0x3A4 */ Vec3f unk_3A4;
    /* 0x3B0 */ Vec3f unk_3B0;
    /* 0x3BC */ Vec3f unk_3BC;
    /* 0x3C8 */ s16 unk_3C8;
    /* 0x3CA */ u8 unk_3CA;
    /* 0x3CB */ u8 unk_3CB;
    /* 0x3CC */ u16 unk_3CC;
    /* 0x3CE */ u16 unk_3CE;
    /* 0x3D0 */ u8 unk_3D0;
    /* 0x3D1 */ char unk_3D1[0x3];
} EnJg; // size = 0x3D4

extern const ActorInit En_Jg_InitVars;

#endif // Z_EN_JG_H

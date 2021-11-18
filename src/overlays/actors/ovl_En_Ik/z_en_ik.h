#ifndef Z_EN_IK_H
#define Z_EN_IK_H

#include "global.h"

struct EnIk;

typedef void (*EnIkActionFunc)(struct EnIk*, GlobalContext*);

typedef enum {
    /* 0x00 */ IK_LIMB_NONE,
    /* 0x01 */ IK_LIMB_WAIST,
    /* 0x02 */ IK_LIMB_R_LOWER_PLATE,
    /* 0x03 */ IK_LIMB_R_LEG,
    /* 0x04 */ IK_LIMB_R_FOOT,
    /* 0x05 */ IK_LIMB_L_LOWER_PLATE,
    /* 0x06 */ IK_LIMB_L_LEG,
    /* 0x07 */ IK_LIMB_L_FOOT,
    /* 0x08 */ IK_LIMB_XXX,
    /* 0x09 */ IK_LIMB_XXX,
    /* 0x0A */ IK_LIMB_XXX,
    /* 0x0B */ IK_LIMB_HELMET,
    /* 0x0C */ IK_LIMB_HEAD,
    /* 0x0D */ IK_LIMB_R_UPPER_ARM,
    /* 0x0E */ IK_LIMB_R_FORARM,
    /* 0x0F */ IK_LIMB_R_HAND_ROOT,
    /* 0x10 */ IK_LIMB_AXE,
    /* 0x11 */ IK_LIMB_R_HAND,
    /* 0x12 */ IK_LIMB_L_UPPER_ARM,
    /* 0x13 */ IK_LIMB_L_FOREARM,
    /* 0x14 */ IK_LIMB_L_HAND,
    /* 0x15 */ IK_LIMB_L_SHOULDER_PLATE,
    /* 0x16 */ IK_LIMB_L_UNDER_SHOULDER,
    /* 0x17 */ IK_LIMB_R_SHOULDER_PLATE,
    /* 0x18 */ IK_LIMB_R_UNDER_SHOULDER,
    /* 0x19 */ IK_LIMB_CHEST_PLATE,
    /* 0x1A */ IK_LIMB_BACK_PLATE,
    /* 0x1B */ IK_LIMB_TORSO,
    /* 0x1C */ IK_LIMB_WAIST,
    /* 0x1C */ IK_LIMB_MAX,
} EnIkLimb;

typedef struct {
    /* 0x00 */ char unk_00[0x4];
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3s unk_1C;
    /* 0x1C */ UNK_TYPE1 unk_22[0x2];
    /* 0x24 */ s32 unk_24;
} EnIkStruct; // size = 0x28

typedef struct EnIk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime; // size = 0x44
    /* 0x0188 */ Vec3s jointTable[30]; // size = 0xB4
    /* 0x023C */ Vec3s morphTable[30]; // size = 0xB4
    /* 0x02F0 */ EnIkActionFunc actionFunc;
    /* 0x02F4 */ u8 unk_2F4;
    /* 0x02F5 */ u8 unk_2F5;
    /* 0x02F6 */ s16 unk_2F6;
    /* 0x02F8 */ s16 unk_2F8;
    /* 0x02FA */ s16 unk_2FA;
    /* 0x02FA */ s16 unk_2FC;
    /* 0x02FE */ char unk_2FE[0x2];
    /* 0x0300 */ s32 unk_300;
    /* 0x0304 */ f32 unk_304;
    /* 0x0308 */ f32 unk_308;
    /* 0x030C */ f32 unk_30C;
    /* 0x0310 */ Vec3f unk_310;
    /* 0x031C */ char unk_31C[0x90];
    /* 0x03AC */ ColliderCylinder colliderCylinder; // size = 0x4C
    /* 0x03F8 */ ColliderQuad colliderQuad; // size = 0x80
    /* 0x0478 */ ColliderTris colliderTris; // size = 0x20
    /* 0x0498 */ ColliderTrisElement shieldColliderItems[2];
    /* 0x0550 */ EnIkStruct unk_550[7]; // size = 0x118
} EnIk; // size = 0x668

extern const ActorInit En_Ik_InitVars;

#endif // Z_EN_IK_H

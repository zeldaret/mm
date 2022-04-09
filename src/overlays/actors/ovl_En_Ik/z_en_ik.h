#ifndef Z_EN_IK_H
#define Z_EN_IK_H

#include "global.h"
#include "objects/object_ik/object_ik.h"

struct EnIk;

typedef void (*EnIkActionFunc)(struct EnIk*, GlobalContext*);

#define IK_PARAMS_01 1
#define IK_PARAMS_FF 0xFF

typedef struct {
    /* 0x00 */ Gfx* unk_00;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3s unk_1C;
    /* 0x24 */ s32 unk_24;
} EnIkStruct; // size = 0x28

typedef struct EnIk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[IRON_KNUCKLE_LIMB_MAX];
    /* 0x023C */ Vec3s morphTable[IRON_KNUCKLE_LIMB_MAX];
    /* 0x02F0 */ EnIkActionFunc actionFunc;
    /* 0x02F4 */ u8 drawArmorFlags; // Value is 0 when Iron knuckle has armor, then changes to 5 for when armor is lost
    /* 0x02F5 */ u8 drawEffect;
    /* 0x02F6 */ s16 counter;
    /* 0x02F8 */ s16 unk_2F8;
    /* 0x02FA */ s16 subCamId;
    /* 0x02FC */ s16 invincibilityFrames;
    /* 0x0300 */ s32 effectIndex;
    /* 0x0304 */ f32 effectAlpha;
    /* 0x0308 */ f32 effectScale;
    /* 0x030C */ f32 steamScale;
    /* 0x0310 */ Vec3f limbPos[13];
    /* 0x03AC */ ColliderCylinder colliderCylinder;
    /* 0x03F8 */ ColliderQuad colliderQuad;
    /* 0x0478 */ ColliderTris colliderTris;
    /* 0x0498 */ ColliderTrisElement shieldColliderItems[2];
    /* 0x0550 */ EnIkStruct unk_550[7];
} EnIk; // size = 0x668

extern const ActorInit En_Ik_InitVars;

#endif // Z_EN_IK_H

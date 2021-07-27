#ifndef Z_EN_HG_H
#define Z_EN_HG_H

#include <global.h>

struct EnHg;

typedef void (*EnHgActionFunc)(struct EnHg*, GlobalContext*);

typedef enum {
    /* 00 */ HG_LIMB_NONE,
    /* 01 */ HG_LIMB_ABDOMEN,
    /* 02 */ HG_LIMB_CHEST,
    /* 03 */ HG_LIMB_SHOULDER_LEFT,
    /* 04 */ HG_LIMB_ARM_LEFT,
    /* 05 */ HG_LIMB_HAND_LEFT,
    /* 06 */ HG_LIMB_SHOULDER_RIGHT,
    /* 07 */ HG_LIMB_ARM_RIGHT,
    /* 08 */ HG_LIMB_HAND_RIGHT,
    /* 09 */ HG_LIMB_EYEBROW,
    /* 10 */ HG_LIMB_HEAD,
    /* 11 */ HG_LIMB_PELVIS,
    /* 12 */ HG_LIMB_THIGH_LEFT,
    /* 13 */ HG_LIMB_LEG_LEFT,
    /* 14 */ HG_LIMB_FOOT_LEFT,
    /* 15 */ HG_LIMB_THIGH_RIGHT,
    /* 16 */ HG_LIMB_LEG_RIGHT,
    /* 17 */ HG_LIMB_FOOT_RIGHT,
    /* 19 */ HG_LIMB_UNK,
    /* 20 */ HG_LIMB_MAX,
} ObjectHgLimbs;

typedef struct EnHg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnHgActionFunc actionFunc;
    /* 0x1D8 */ MtxF unk1D8;
    /* 0x218 */ s32 unk218;
    /* 0x21C */ s32 currentAnimation;
    /* 0x220 */ Vec3s limbDrawTbl[HG_LIMB_MAX];
    /* 0x292 */ Vec3s transitionDrawTbl[HG_LIMB_MAX];
    /* 0x304 */ UNK_TYPE1 pad304[0xC];
    /* 0x310 */ u16 cutscenes[4];
} EnHg; // size = 0x318

extern const ActorInit En_Hg_InitVars;

#endif // Z_EN_HG_H

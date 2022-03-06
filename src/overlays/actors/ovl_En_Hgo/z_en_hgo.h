#ifndef Z_EN_HGO_H
#define Z_EN_HGO_H

#include "global.h"

struct EnHgo;

typedef void (*EnHgoActionFunc)(struct EnHgo*, GlobalContext*);

// Shares the same setup as en_hg
typedef enum {
    /* 00 */ HGO_LIMB_NONE,
    /* 01 */ HGO_LIMB_ABDOMEN,
    /* 02 */ HGO_LIMB_CHEST,
    /* 03 */ HGO_LIMB_SHOULDER_LEFT,
    /* 04 */ HGO_LIMB_ARM_LEFT,
    /* 05 */ HGO_LIMB_HAND_LEFT,
    /* 06 */ HGO_LIMB_SHOULDER_RIGHT,
    /* 07 */ HGO_LIMB_ARM_RIGHT,
    /* 08 */ HGO_LIMB_HAND_RIGHT,
    /* 09 */ HGO_LIMB_EYEBROW,
    /* 10 */ HGO_LIMB_HEAD,
    /* 11 */ HGO_LIMB_PELVIS,
    /* 12 */ HGO_LIMB_THIGH_LEFT,
    /* 13 */ HGO_LIMB_LEG_LEFT,
    /* 14 */ HGO_LIMB_FOOT_LEFT,
    /* 15 */ HGO_LIMB_THIGH_RIGHT,
    /* 16 */ HGO_LIMB_LEG_RIGHT,
    /* 17 */ HGO_LIMB_FOOT_RIGHT,
    /* 18 */ HGO_LIMB_UNK,
    /* 19 */ HGO_LIMB_MAX,
} ObjectHgoLimbs;

typedef struct EnHgo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnHgoActionFunc actionFunc;
    /* 0x1D8 */ MtxF unk_1D8;
    /* 0x218 */ s32 unk_218;
    /* 0x21C */ Vec3s jointTable[HGO_LIMB_MAX];
    /* 0x28E */ Vec3s morphTable[HGO_LIMB_MAX];
    /* 0x300 */ Vec3s unk_300;
    /* 0x306 */ Vec3s unk_306;
    /* 0x30C */ s16 unk_30C;
    /* 0x30E */ s16 unk_30E;
    /* 0x310 */ s16 unk_310;
    /* 0x312 */ s16 unk_312;
    /* 0x314 */ u16 unk_314;
    /* 0x316 */ u16 unk_316;
} EnHgo; // size = 0x318

extern const ActorInit En_Hgo_InitVars;

#endif // Z_EN_HGO_H

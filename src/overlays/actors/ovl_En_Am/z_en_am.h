#ifndef Z_EN_AM_H
#define Z_EN_AM_H

#include "global.h"

struct EnAm;

typedef void (*EnAmActionFunc)(struct EnAm*, GlobalContext*);

typedef enum {
    /* 00 */ AM_LIMB_NONE,
    /* 01 */ AM_LIMB_EMPTY_1,
    /* 02 */ AM_LIMB_2,
    /* 03 */ AM_LIMB_BODY,
    /* 04 */ AM_LIMB_EMPTY_4,
    /* 05 */ AM_LIMB_EMPTY_5,
    /* 06 */ AM_LIMB_SHIELD,
    /* 07 */ AM_LIMB_EMPTY_7,
    /* 08 */ AM_LIMB_EMPTY_8,
    /* 09 */ AM_LIMB_SWORD,
    /* 10 */ AM_LIMB_EMPTY_10,
    /* 11 */ AM_LIMB_EMPTY_11,
    /* 12 */ AM_LIMB_BASE,
    /* 13 */ AM_LIMB_UNK,
    /* 14 */ AM_LIMB_MAX,
} ObjectAmLimbs;

typedef struct EnAm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[AM_LIMB_MAX];
    /* 0x01DC */ Vec3s morphTable[AM_LIMB_MAX];
    /* 0x0230 */ EnAmActionFunc actionFunc;
    /* 0x0234 */ u8 textureBlend; // 0 = statue textures; 255 = enemy textures
    /* 0x0236 */ s16 explodeTimer; // timer counting down till armos explodes
    /* 0x0238 */ s16 returnHomeTimer; // Timer that counts down till an armos will return to its spawn position
    /* 0x023A */ s16 unkFlag;
    /* 0x023C */ s16 armosYaw; // Yaw of Armos
    /* 0x0240 */ f32 speed; // Hopping speed of Armos
    /* 0x0244 */ f32 effectAlpha;
    /* 0x0248 */ f32 effectScale;
    /* 0x024C */ Vec3f limbPos[13];
    /* 0x02E8 */ ColliderCylinder enemyCollider; // Collider for when Armos is Hostile
    /* 0x0334 */ ColliderCylinder interactCollider; // Collider for when an interactable Armos is docile
} EnAm; // size = 0x380

extern const ActorInit En_Am_InitVars;

#endif // Z_EN_AM_H

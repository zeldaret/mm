#ifndef Z_EN_AM_H
#define Z_EN_AM_H

#include "global.h"

struct EnAm;

typedef void (*EnAmActionFunc)(struct EnAm*, GlobalContext*);

typedef enum {
    /* 00 */ AM_LIMB_NONE,
    /* 01 */ AM_LIMB_1,
    /* 02 */ AM_LIMB_2,
    /* 03 */ AM_LIMB_3,
    /* 04 */ AM_LIMB_4,
    /* 05 */ AM_LIMB_5,
    /* 06 */ AM_LIMB_6,
    /* 07 */ AM_LIMB_7,
    /* 08 */ AM_LIMB_8,
    /* 09 */ AM_LIMB_9,
    /* 10 */ AM_LIMB_10,
    /* 11 */ AM_LIMB_11,
    /* 12 */ AM_LIMB_12,
    /* 13 */ AM_LIMB_13,
    /* 14 */ AM_LIMB_MAX,
} ObjectAmLimbs;

typedef struct EnAm {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[14];
    /* 0x01DC */ Vec3s morphTable[14];
    /* 0x0230 */ EnAmActionFunc actionFunc;
    /* 0x0234 */ u8 textureBlend; // 0 = statue textures; 255 = enemy textures
    /* 0x0235 */ s8 unk_235;
    /* 0x0236 */ s16 explodeTimer;
    /* 0x0238 */ s16 returnHomeTimer;
    /* 0x023A */ s16 unk_23A;
    /* 0x023C */ s16 unk_23C;
    /* 0x023C */ s16 unk_23D;
    /* 0x023C */ f32 unk_240;
    /* 0x0244 */ f32 unk_244;
    /* 0x0248 */ f32 unk_248;
    /* 0x024C */ Vec3f limbPos[13];
    /* 0x02E8 */ ColliderCylinder enemyCollider;
    /* 0x0334 */ ColliderCylinder interactCollider;
} EnAm; // size = 0x380

extern const ActorInit En_Am_InitVars;

#endif // Z_EN_AM_H

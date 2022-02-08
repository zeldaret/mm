#ifndef Z_EN_BIGOKUTA_H
#define Z_EN_BIGOKUTA_H

#include "global.h"

struct EnBigokuta;

typedef void (*EnBigokutaActionFunc)(struct EnBigokuta*, GlobalContext*);
typedef void (*EnBigokutaUnkFunc)(GlobalContext*, struct EnBigokuta*);

typedef enum {
    /* 00 */ BIGOKUTA_LIMB_NONE,
    /* 01 */ BIGOKUTA_LIMB_BODY,
    /* 02 */ BIGOKUTA_LIMB_ARM_BASE_RIGHT_FRONT,
    /* 03 */ BIGOKUTA_LIMB_ARM_END_RIGHT_FRONT,
    /* 04 */ BIGOKUTA_LIMB_ARM_BASE_LEFT_FRONT,
    /* 05 */ BIGOKUTA_LIMB_ARM_END_LEFT_FRONT,
    /* 06 */ BIGOKUTA_LIMB_ARM_BASE_RIGHT_BACK,
    /* 07 */ BIGOKUTA_LIMB_ARM_END_RIGHT_BACK,
    /* 08 */ BIGOKUTA_LIMB_ARM_BASE_LEFT_BACK,
    /* 09 */ BIGOKUTA_LIMB_ARM_END_LEFT_BACK,
    /* 10 */ BIGOKUTA_LIMB_HEAD,
    /* 11 */ BIGOKUTA_LIMB_TENTACLE_BASE_LEFT,
    /* 12 */ BIGOKUTA_LIMB_TENTACLE_TIP_LEFT,
    /* 13 */ BIGOKUTA_LIMB_TENTACLE_BASE_RIGHT,
    /* 14 */ BIGOKUTA_LIMB_TENTACLE_TIP_RIGHT,
    /* 15 */ BIGOKUTA_LIMB_WEAK_POINT_LEFT,
    /* 16 */ BIGOKUTA_LIMB_WEAK_POINT_RIGHT,
    /* 17 */ BIGOKUTA_LIMB_SNOUT_CENTER,
    /* 18 */ BIGOKUTA_LIMB_SNOUT_RIGHT,
    /* 19 */ BIGOKUTA_LIMB_SNOUT_LEFT,
    /* 20 */ BIGOKUTA_LIMB_MAX
} ObjectBigokutaLimbs;

typedef struct EnBigokuta {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnBigokutaUnkFunc unkFunc; // possibly something to do with photographing
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ EnBigokutaActionFunc actionFunc;
    /* 0x0190 */ u8 drawDmgEffType;
    /* 0x0192 */ s16 timer;
    /* 0x0194 */ s16 camId;
    /* 0x0196 */ s16 cutscene;
    /* 0x0198 */ Vec3s jointTable[BIGOKUTA_LIMB_MAX];
    /* 0x0210 */ Vec3s morphTable[BIGOKUTA_LIMB_MAX];
    /* 0x0288 */ f32 drawDmgEffAlpha;
    /* 0x028C */ f32 drawDmgEffScale;
    /* 0x0290 */ f32 drawDmgEffFrozenSteamScale; // only affects DRAWEFFECT_ICE
    /* 0x0294 */ Vec3f playerPos;
    /* 0x02A0 */ Vec3f playerHoldPos;
    /* 0x02AC */ Vec3f camAt;
    /* 0x02B8 */ Vec3f camEye;
    /* 0x02C4 */ Vec3f limbPos[13];
    /* 0x0360 */ ColliderCylinder shellCollider;
    /* 0x03AC */ ColliderCylinder bodyCollider;
} EnBigokuta; // size = 0x3F8

extern const ActorInit En_Bigokuta_InitVars;

#endif // Z_EN_BIGOKUTA_H

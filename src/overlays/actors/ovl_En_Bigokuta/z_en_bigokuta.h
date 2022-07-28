#ifndef Z_EN_BIGOKUTA_H
#define Z_EN_BIGOKUTA_H

#include "global.h"
#include "assets/objects/object_bigokuta/object_bigokuta.h"

struct EnBigokuta;

typedef void (*EnBigokutaActionFunc)(struct EnBigokuta*, PlayState*);
typedef void (*EnBigokutaUnkFunc)(PlayState*, struct EnBigokuta*);

typedef struct EnBigokuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnBigokutaUnkFunc unkFunc; // possibly something to do with photographing
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ EnBigokutaActionFunc actionFunc;
    /* 0x190 */ u8 drawDmgEffType;
    /* 0x192 */ s16 timer;
    /* 0x194 */ s16 subCamId;
    /* 0x196 */ s16 cutscene;
    /* 0x198 */ Vec3s jointTable[BIGOKUTA_LIMB_MAX];
    /* 0x210 */ Vec3s morphTable[BIGOKUTA_LIMB_MAX];
    /* 0x288 */ f32 drawDmgEffAlpha;
    /* 0x28C */ f32 drawDmgEffScale;
    /* 0x290 */ f32 drawDmgEffFrozenSteamScale; // only affects DRAWEFFECT_ICE
    /* 0x294 */ Vec3f playerPos;
    /* 0x2A0 */ Vec3f playerHoldPos;
    /* 0x2AC */ Vec3f subCamAt;
    /* 0x2B8 */ Vec3f subCamEye;
    /* 0x2C4 */ Vec3f limbPos[13];
    /* 0x360 */ ColliderCylinder shellCollider;
    /* 0x3AC */ ColliderCylinder bodyCollider;
} EnBigokuta; // size = 0x3F8

extern const ActorInit En_Bigokuta_InitVars;

#endif // Z_EN_BIGOKUTA_H

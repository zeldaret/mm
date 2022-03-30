#ifndef Z_EN_FLOORMAS_H
#define Z_EN_FLOORMAS_H

#include "global.h"
#include "objects/object_wallmaster/object_wallmaster.h"

struct EnFloormas;

typedef void (*EnFloormasActionFunc)(struct EnFloormas*, GlobalContext*);

#define ENFLOORMAS_GET_7FFF(thisx) ((thisx)->params & 0x7FFF)
#define ENFLOORMAS_GET_8000(thisx) ((thisx)->params & 0x8000)

enum {
    /* 0x00 */ ENFLOORMAS_GET_7FFF_0,
    /* 0x10 */ ENFLOORMAS_GET_7FFF_10 = 0x10,
    /* 0x20 */ ENFLOORMAS_GET_7FFF_20 = 0x20,
    /* 0x40 */ ENFLOORMAS_GET_7FFF_40 = 0x40,
};

typedef struct EnFloormas {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnFloormasActionFunc actionFunc;
    /* 0x018C */ u8 drawDmgEffType;
    /* 0x018E */ s16 unk_18E;
    /* 0x0190 */ s16 unk_190;
    /* 0x0192 */ s16 unk_192;
    /* 0x0194 */ s16 unk_194;
    /* 0x0196 */ Vec3s jointTable[WALLMASTER_LIMB_MAX];
    /* 0x022C */ Vec3s morphTable[WALLMASTER_LIMB_MAX];
    /* 0x02C4 */ f32 drawDmgEffAlpha;
    /* 0x02C8 */ f32 drawDmgEffScale;
    /* 0x02CC */ f32 drawDmgEffFrozenSteamScale;
    /* 0x02D0 */ Vec3f limbPos[11];
    /* 0x0354 */ ColliderCylinder collider;
} EnFloormas; // size = 0x3A0

extern const ActorInit En_Floormas_InitVars;

#endif // Z_EN_FLOORMAS_H

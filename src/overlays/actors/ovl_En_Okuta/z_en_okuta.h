#ifndef Z_EN_OKUTA_H
#define Z_EN_OKUTA_H

#include "global.h"
#include "objects/object_okuta/object_okuta.h"

struct EnOkuta;

typedef void (*EnOkutaActionFunc)(struct EnOkuta*, PlayState*);

#define EN_OKUTA_GET_UNK190(thisx) (((thisx)->params >> 8) & 0xFF)
#define EN_OKUTA_GET_TYPE(thisx) ((thisx)->params)

typedef struct EnOkuta {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnOkutaActionFunc actionFunc;
    /* 0x18C */ u8 drawDmgEffType;
    /* 0x18E */ s16 unk18E;
    /* 0x190 */ s16 unk190;
    /* 0x192 */ Vec3s jointTable[OCTOROK_LIMB_MAX];
    /* 0x1F2 */ Vec3s morphTable[OCTOROK_LIMB_MAX];
    /* 0x254 */ f32 drawDmgEffAlpha;
    /* 0x258 */ f32 drawDmgEffScale;
    /* 0x25C */ f32 drawDmgEffFrozenSteamScale;
    /* 0x260 */ f32 unk260;
    /* 0x264 */ Vec3f headScale;
    /* 0x270 */ Vec3f bodyPartsPos[10];
    /* 0x2E8 */ ColliderCylinder collider;
} EnOkuta; // size = 0x334

#endif // Z_EN_OKUTA_H

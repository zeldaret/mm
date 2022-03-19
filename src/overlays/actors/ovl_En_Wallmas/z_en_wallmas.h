#ifndef Z_EN_WALLMAS_H
#define Z_EN_WALLMAS_H

#include "global.h"
#include "objects/object_wallmaster/object_wallmaster.h"

#define EN_WALLMAS_GET_TYPE(thisx) ((thisx)->params)
#define EN_WALLMAS_GET_SWITCH_FLAG(thisx) (((thisx)->params >> 8) & 0xFF)
#define EN_WALLMAS_IS_FROZEN(thisx) ((thisx)->params & 0x80)

struct EnWallmas;

typedef void (*EnWallmasActionFunc)(struct EnWallmas*, GlobalContext*);

typedef struct EnWallmas {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnWallmasActionFunc actionFunc;
    /* 0x18C */ u8 unk_18C;
    /* 0x18E */ s16 timer;
    /* 0x190 */ s16 switchFlag;
    /* 0x192 */ Vec3s jointTable[WALLMASTER_LIMB_MAX];
    /* 0x228 */ Vec3s morphTable[WALLMASTER_LIMB_MAX];
    /* 0x2C0 */ f32 unk_2C0;
    /* 0x2C4 */ f32 unk_2C4;
    /* 0x2C8 */ f32 unk_2C8;
    /* 0x2CC */ f32 unk_2CC;
    /* 0x2D0 */ f32 unk_2D0;
    /* 0x2D4 */ Vec3f limbPos[11];
    /* 0x358 */ ColliderCylinder collider;
} EnWallmas; // size = 0x3A4

extern const ActorInit En_Wallmas_InitVars;

#endif // Z_EN_WALLMAS_H

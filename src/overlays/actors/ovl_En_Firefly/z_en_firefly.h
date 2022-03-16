#ifndef Z_EN_FIREFLY_H
#define Z_EN_FIREFLY_H

#include "global.h"

struct EnFirefly;

typedef void (*EnFireflyActionFunc)(struct EnFirefly*, GlobalContext*);

typedef enum {
    /* 0 */ KEESE_FIRE_FLY,
    /* 2 */ KEESE_NORMAL_FLY = 2,
    /* 3 */ KEESE_NORMAL_PERCH,
    /* 4 */ KEESE_ICE_FLY
} KeeseMainType;

#define KEESE_INVISIBLE (1 << 0xF)
#define KEESE_GET_MAIN_TYPE(thisx) ((thisx)->params & 0x7FFF)

typedef struct EnFirefly {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnFireflyActionFunc actionFunc;
    /* 0x18C */ u8 auraType;
    /* 0x18D */ u8 currentType;
    /* 0x18E */ u8 isInvisible;
    /* 0x18F */ u8 drawDmgEffType;
    /* 0x190 */ s16 timer;
    /* 0x192 */ s16 targetPitch;
    /* 0x194 */ Vec3s jointTable[28];
    /* 0x23C */ Vec3s morphTable[28];
    /* 0x2E4 */ f32 maxAltitude;
    /* 0x2E8 */ f32 drawDmgEffAlpha;
    /* 0x2E8 */ f32 drawDmgEffScale;
    /* 0x2E8 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x2F4 */ u32 unk_2F4;
    /* 0x2F8 */ Vec3f limbPos[3];
    /* 0x31C */ ColliderSphere collider;
} EnFirefly; // size = 0x374

extern const ActorInit En_Firefly_InitVars;

#endif // Z_EN_FIREFLY_H

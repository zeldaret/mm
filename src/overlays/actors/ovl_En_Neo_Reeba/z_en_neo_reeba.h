#ifndef Z_EN_NEO_REEBA_H
#define Z_EN_NEO_REEBA_H

#include "global.h"
#include "objects/object_rb/object_rb.h"

#define EN_NEO_REEBA_IS_LARGE(thisx) ((thisx)->params & 0x8000)

struct EnNeoReeba;

typedef void (*EnNeoReebaActionFunc)(struct EnNeoReeba*, GlobalContext*);

typedef struct EnNeoReeba {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ ColliderCylinder collider;
    /* 0x1D4 */ Vec3s jointTable[LEEVER_LIMB_MAX];
    /* 0x240 */ Vec3s morphTable[LEEVER_LIMB_MAX];
    /* 0x2AC */ EnNeoReebaActionFunc actionFunc;
    /* 0x2B0 */ Vec3f targetPos;
    /* 0x2BC */ Vec3f velToTarget;
    /* 0x2C8 */ Vec3f limbPos[4];
    /* 0x2F8 */ f32 sinkRiseRate;
    /* 0x2FC */ f32 rotationSpeed;
    /* 0x300 */ f32 drawEffectAlpha;
    /* 0x304 */ f32 drawEffectScale;
    /* 0x308 */ s16 rotationAngle;
    /* 0x30A */ s16 actionTimer;
    /* 0x30C */ s16 sfxTimer;
    /* 0x30E */ s16 stunTimer;
    /* 0x310 */ u8 drawEffectType;
} EnNeoReeba; // size = 0x314

extern const ActorInit En_Neo_Reeba_InitVars;

#endif // Z_EN_NEO_REEBA_H

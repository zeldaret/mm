#ifndef Z_EN_NEO_REEBA_H
#define Z_EN_NEO_REEBA_H

#include "global.h"

#define EN_NEO_REEBA_IS_LARGE(thisx) ((thisx)->params & 0x8000)

struct EnNeoReeba;

typedef void (*EnNeoReebaActionFunc)(struct EnNeoReeba*, GlobalContext*);

typedef struct EnNeoReeba {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ ColliderCylinder collider;
    /* 0x01d4 */ Vec3s jointTable[18];
    /* 0x0240 */ Vec3s morphTable[18];
    /* 0x02AC */ EnNeoReebaActionFunc actionFunc;
    /* 0x02B0 */ Vec3f targetPos;
    /* 0x02BC */ Vec3f velToTarget;
    /* 0x02C8 */ Vec3f limbPos[4];
    /* 0x02F8 */ f32 sinkRiseRate;
    /* 0x02FC */ f32 rotationSpeed;
    /* 0x0300 */ f32 drawEffectAlpha;
    /* 0x0304 */ f32 drawEffectScale;
    /* 0x0308 */ s16 rotationAngle;
    /* 0x030A */ s16 actionTimer;
    /* 0x030C */ s16 sfxTimer;
    /* 0x030E */ s16 stunTimer;
    /* 0x0310 */ u8 drawEffectType;
} EnNeoReeba; // size = 0x314

extern const ActorInit En_Neo_Reeba_InitVars;

#endif // Z_EN_NEO_REEBA_H

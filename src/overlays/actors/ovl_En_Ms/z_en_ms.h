#ifndef Z_EN_MS_H
#define Z_EN_MS_H

#include "global.h"

struct EnMs;

typedef void (*EnMsActionFunc)(struct EnMs*, GlobalContext*);

typedef struct EnMs {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[9];
    /* 0x1BE */ Vec3s morphTable[9];
    /* 0x1F4 */ EnMsActionFunc actionFunc;
    /* 0x1F8 */ ColliderCylinder collider;
} EnMs; // size = 0x244

extern const ActorInit En_Ms_InitVars;

#endif // Z_EN_MS_H

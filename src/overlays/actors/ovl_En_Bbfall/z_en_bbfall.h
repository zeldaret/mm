#ifndef Z_EN_BBFALL_H
#define Z_EN_BBFALL_H

#include "global.h"

struct EnBbfall;

typedef void (*EnBbfallActionFunc)(struct EnBbfall*, GlobalContext*);

typedef struct EnBbfall {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[16];
    /* 0x1E8 */ Vec3s morphTable[16];
    /* 0x248 */ EnBbfallActionFunc actionFunc;
    /* 0x24C */ char unk_24C[0x4];
    /* 0x250 */ s16 unk_250;
    /* 0x252 */ char unk_252[0x132];
    /* 0x384 */ ColliderJntSph collider;
    /* 0x3A4 */ ColliderJntSphElement colliderElements[3];
} EnBbfall; // size = 0x464

extern const ActorInit En_Bbfall_InitVars;

#endif // Z_EN_BBFALL_H

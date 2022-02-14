#ifndef Z_EN_INSECT_H
#define Z_EN_INSECT_H

#include "global.h"

struct EnInsect;

typedef void (*EnInsectActionFunc)(struct EnInsect*, GlobalContext*);

#define ENINSECT_GET_1(thisx) ((thisx)->params & 1)

typedef struct EnInsect {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderJntSph collider;
    /* 0x0164 */ ColliderJntSphElement colliderElements[1];
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x01E8 */ Vec3s jointTable[24];
    /* 0x0278 */ Vec3s morphTable[24];
    /* 0x0308 */ EnInsectActionFunc actionFunc;
    /* 0x030C */ u16 unk_30C;
    /* 0x030E */ s16 unk_30E;
    /* 0x0310 */ s16 unk_310;
    /* 0x0312 */ s16 unk_312;
    /* 0x0314 */ s16 unk_314;
    /* 0x0316 */ s16 unk_316;
} EnInsect; // size = 0x318

extern const ActorInit En_Insect_InitVars;

#endif // Z_EN_INSECT_H

#ifndef Z_EN_INSECT_H
#define Z_EN_INSECT_H

#include "global.h"

struct EnInsect;

typedef void (*EnInsectActionFunc)(struct EnInsect*, PlayState*);

#define ENINSECT_GET_1(thisx) ((thisx)->params & 1)

typedef struct EnInsect {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderJntSph collider;
    /* 0x164 */ ColliderJntSphElement colliderElements[1];
    /* 0x1A4 */ SkelAnime skelAnime;
    /* 0x1E8 */ Vec3s jointTable[24];
    /* 0x278 */ Vec3s morphTable[24];
    /* 0x308 */ EnInsectActionFunc actionFunc;
    /* 0x30C */ u16 unk_30C;
    /* 0x30E */ s16 unk_30E;
    /* 0x310 */ s16 unk_310;
    /* 0x312 */ s16 unk_312;
    /* 0x314 */ s16 unk_314;
    /* 0x316 */ s16 unk_316;
} EnInsect; // size = 0x318

extern const ActorInit En_Insect_InitVars;

#endif // Z_EN_INSECT_H

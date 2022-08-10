#ifndef Z_EN_RZ_H
#define Z_EN_RZ_H

#include "global.h"

#define EN_RZ_GET_PARAM_F(thisx) ((thisx)->params & 0xF)

struct EnRz;

typedef void (*EnRzActionFunc)(struct EnRz*, PlayState*);

typedef struct EnRz {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelanime;
    /* 0x188 */ char pad188[0x230];                 /* maybe part of skelanime[9]? */
    /* 0x3B8 */ Path *unk3B8;
    /* 0x3BC */ s32 unk3BC;
    /* 0x3C0 */ ColliderCylinder collider;
    /* 0x40C */ Actor *unk40C;
    /* 0x410 */ s16 unk410;                         /* inferred */
    /* 0x412 */ s16 unk412;                         /* inferred */
    /* 0x414 */ Vec3f unk414;
    /* 0x420 */ u16 unk420;
    /* 0x422 */ s16 unk422;
    /* 0x424 */ s16 unk424;
    /* 0x426 */ u16 unk426;
    /* 0x428 */ u16 unk428;
    /* 0x42A */ s16 unk42A;
    /* 0x42C */ s16 unk42C;
    /* 0x42E */ char pad42E[2];
    /* 0x430 */ EnRzActionFunc actionFunc;
} EnRz; // size = 0x434

extern const ActorInit En_Rz_InitVars;

#endif // Z_EN_RZ_H

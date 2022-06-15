#ifndef Z_EN_STH_H
#define Z_EN_STH_H

#include "global.h"

struct EnSth;

typedef void (*EnSthActionFunc)(struct EnSth*, GlobalContext*);

#define ENSTH_GET_F(thisx) ((thisx)->params & 0xF)
#define ENSTH_GET_100(thisx) ((thisx)->params & 0x100)

enum {
    /* 1 */ ENSTH_F_1 = 1,
    /* 2 */ ENSTH_F_2,
    /* 3 */ ENSTH_F_3,
    /* 4 */ ENSTH_F_4,
    /* 5 */ ENSTH_F_5,
};

typedef struct EnSth {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder collider;
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ Vec3s jointTable[16];
    /* 0x234 */ Vec3s morphTable[16];
    /* 0x294 */ Vec3s unk_294;
    /* 0x29A */ s16 unk_29A;
    /* 0x29C */ u16 unk_29C;
    /* 0x29E */ u8 unk_29E;
    /* 0x29F */ u8 unk_29F;
    /* 0x2A0 */ EnSthActionFunc actionFunc;
} EnSth; // size = 0x2A4

extern const ActorInit En_Sth_InitVars;

#endif // Z_EN_STH_H

#ifndef Z_EN_RD_H
#define Z_EN_RD_H

#include "global.h"

struct EnRd;

typedef void (*EnRdActionFunc)(struct EnRd*, GlobalContext*);
typedef void (*EnRdFunc)(struct EnRd*);

#define ENRD_GET_80(thisx) ((thisx)->params & 0x80)
#define ENRD_GET_FF00(thisx) (((thisx)->params & 0xFF00) >> 8)

enum {
    /*   -2 */ ENRD_GET_MINUS_2 = -2,
    /*   -1 */ ENRD_GET_MINUS_1 = -1,
    /* 0x00 */ ENRD_GET_0 = 0,
    /* 0x01 */ ENRD_GET_1,
    /* 0x02 */ ENRD_GET_2,
    /* 0x03 */ ENRD_GET_3,
    /* 0x04 */ ENRD_GET_4,
    /* 0x05 */ ENRD_GET_5,
};

typedef struct EnRd {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnRdActionFunc actionFunc;
    /* 0x018C */ EnRdFunc unkFunc;
    /* 0x0190 */ ColliderCylinder collider;
    /* 0x01DC */ Vec3f unk_1DC[15];
    /* 0x0290 */ s32 unk_290;
    /* 0x0294 */ f32 unk_294;
    /* 0x0298 */ f32 unk_298;
    /* 0x029C */ Vec3s jointTable[26];
    /* 0x0338 */ Vec3s morphTable[26];
    /* 0x03D4 */ s16 unk_3D4;
    /* 0x03D6 */ s16 unk_3D6;
    /* 0x03D8 */ s16 unk_3D8;
    /* 0x03DA */ s16 unk_3DA;
    /* 0x03DC */ s16 unk_3DC;
    /* 0x03DE */ s16 unk_3DE;
    /* 0x03E0 */ s16 unk_3E0;
    /* 0x03E2 */ s16 unk_3E2;
    /* 0x03E4 */ s16 unk_3E4;
    /* 0x03E6 */ s16 unk_3E6;
    /* 0x03E8 */ u8 unk_3E8;
    /* 0x03E9 */ u8 unk_3E9;
    /* 0x03EA */ u8 unk_3EA;
    /* 0x03EB */ u8 unk_3EB;
    /* 0x03EC */ u8 unk_3EC;
    /* 0x03ED */ u8 unk_3ED;
    /* 0x03EE */ u8 unk_3EE;
    /* 0x03EF */ u8 unk_3EF;
    /* 0x03F0 */ u8 unk_3F0;
    /* 0x03F1 */ s8 unk_3F1;
} EnRd; // size = 0x3F4

extern const ActorInit En_Rd_InitVars;

#endif // Z_EN_RD_H

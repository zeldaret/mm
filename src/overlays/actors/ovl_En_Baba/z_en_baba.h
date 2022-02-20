#ifndef Z_EN_BABA_H
#define Z_EN_BABA_H

#include "global.h"

struct EnBaba;

typedef void (*EnBabaActionFunc)(struct EnBaba*, GlobalContext*);

#define ENBABA_GET_3F00(thisx) (((thisx)->params & 0x3F00) >> 8)
#define ENBABA_GET_C000(thisx) (((thisx)->params & 0xC000) >> 0xE)

#define ENBABA_3F00_3F 0x3F

enum {
    /* 0 */ ENBABA_C000_0,
    /* 1 */ ENBABA_C000_1,
    /* 2 */ ENBABA_C000_2,
};

typedef struct EnBaba {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ struct EnOssan* unk_144;
    /* 0x0148 */ EnBabaActionFunc actionFunc;
    /* 0x014C */ UNK_TYPE1 unk14C[4];
    /* 0x0150 */ SkelAnime skelAnime;
    /* 0x0194 */ ColliderCylinder collider;
    /* 0x01E0 */ u16 unk_1E0;
    /* 0x01E2 */ u8 unk_1E2;
    /* 0x01E4 */ Path* path;
    /* 0x01E8 */ s16 unk_1E8;
    /* 0x01EA */ UNK_TYPE1 unk1EA[0x1C];
    /* 0x0206 */ Vec3s jointTable[18];
    /* 0x0272 */ Vec3s morphTable[18];
    /* 0x02DE */ Vec3s unk_2DE;
    /* 0x02E4 */ Vec3s unk_2E4;
    /* 0x02EA */ Vec3s unk_2EA;
    /* 0x02F0 */ UNK_TYPE1 unk2F0[0x12];
    /* 0x0302 */ s16 unk_302[18];
    /* 0x0326 */ s16 unk_326[18];
    /* 0x034A */ UNK_TYPE1 unk34A[0xBA];
    /* 0x0404 */ s16 unk_404;
    /* 0x0406 */ UNK_TYPE1 unk406[4];
    /* 0x040A */ u16 unk_40A;
    /* 0x040C */ s32 unk_40C;
    /* 0x0410 */ Path* unk_410;
    /* 0x0414 */ Vec3f unk_414;
    /* 0x0420 */ f32 unk_420;
    /* 0x0424 */ s32 unk_424;
    /* 0x0428 */ s32 unk_428;
    /* 0x042C */ s32 unk_42C;
    /* 0x0430 */ s32 unk_430;
    /* 0x0434 */ u8 unk_434;
    /* 0x0436 */ s16 unk_436;
    /* 0x0438 */ s32 unk_438;
    /* 0x043C */ s32 unk_43C;
} EnBaba; // size = 0x440

extern const ActorInit En_Baba_InitVars;

#endif // Z_EN_BABA_H

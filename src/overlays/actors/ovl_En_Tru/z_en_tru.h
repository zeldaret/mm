#ifndef Z_EN_TRU_H
#define Z_EN_TRU_H

#include "global.h"

struct EnTru;

typedef void (*EnTruActionFunc)(struct EnTru*, GlobalContext*);
typedef s32 (*EnTruUnkFunc)(Actor*, GlobalContext*);

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ Vec3f unk_04;
    /* 0x10 */ Vec3f unk_10;
    /* 0x1C */ Vec3f unk_1C;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
} EnTruUnkStruct; // size = 0x30

typedef struct EnTru {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnTruActionFunc actionFunc;
    /* 0x018C */ ColliderSphere collider;
    /* 0x01E4 */ Path* path;
    /* 0x01E8 */ s32 unk_1E8;
    /* 0x01EC */ Vec3f unk_1EC;
    /* 0x01F8 */ Vec3f unk_1F8;
    /* 0x0204 */ Vec3s unk_204;
    /* 0x020A */ Vec3s jointTable[27];
    /* 0x02AC */ Vec3s morphTable[27];
    /* 0x034E */ u16 unk_34E;
    /* 0x0350 */ UNK_TYPE1 unk350[0x4];
    /* 0x0354 */ s32* unk_354;
    /* 0x0358 */ f32 unk_358;
    /* 0x035C */ f32 unk_35C;
    /* 0x0360 */ s16 unk_360;
    /* 0x0362 */ s16 unk_362;
    /* 0x0364 */ s16 unk_364;
    /* 0x0366 */ s16 unk_366;
    /* 0x0368 */ s16 unk_368;
    /* 0x036A */ s16 unk_36A;
    /* 0x036C */ s16 unk_36C;
    /* 0x036E */ s16 unk_36E;
    /* 0x0370 */ s16 unk_370;
    /* 0x0372 */ s16 unk_372;
    /* 0x0374 */ s16 unk_374;
    /* 0x0378 */ EnTruUnkFunc unk_378;
    /* 0x037C */ s32 unk_37C;
    /* 0x0380 */ UNK_TYPE1 unk380[0x4];
    /* 0x0384 */ s32 unk_384;
    /* 0x0388 */ s32 unk_388;
    /* 0x038C */ s32 unk_38C;
    /* 0x0390 */ s32 unk_390;
    /* 0x0394 */ EnTruUnkStruct unk_394[30];
} EnTru; // size = 0x934

extern const ActorInit En_Tru_InitVars;

#endif // Z_EN_TRU_H

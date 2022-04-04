#ifndef Z_EN_JA_H
#define Z_EN_JA_H

#include "global.h"

struct EnJa;

typedef void (*EnJaActionFunc)(struct EnJa*, GlobalContext*);

#define ENJA_GET_3(thisx) (((thisx)->params & 3) & 0xFF)

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
} EnJaStruct; // size = 0x10

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ Player* player;
} EnJaStruct2; // size = 0x10

typedef struct EnJa {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnJaActionFunc actionFunc;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ EnJaStruct2 unk_1D8;
    /* 0x01E4 */ Vec3s unk_1E4;
    /* 0x01EC */ Vec3f unk_1EC;
    /* 0x01F8 */ Vec3f unk_1F8;
    /* 0x0204 */ Vec3f unk_204;
    /* 0x0210 */ Vec3f unk_210;
    /* 0x021C */ Vec3f unk_21C;
    /* 0x0228 */ Vec3f unk_228;
    /* 0x0234 */ EnJaStruct unk_234[4];
    /* 0x0274 */ Vec3s unk_274;
    /* 0x027A */ Vec3s unk_27A;
    /* 0x0280 */ Vec3s jointTable[16];
    /* 0x02E0 */ Vec3s morphTable[16];
    /* 0x0340 */ u16 unk_340;
    /* 0x0344 */ f32 unk_344;
    /* 0x0348 */ f32 unk_348;
    /* 0x034C */ f32 unk_34C;
    /* 0x0350 */ UNK_TYPE1 unk350[0x4];
    /* 0x0354 */ s16 unk_354;
    /* 0x0356 */ s16 unk_356;
    /* 0x0358 */ s16 unk_358;
    /* 0x035A */ s16 unk_35A;
    /* 0x035C */ s16 unk_35C;
    /* 0x035E */ s16 unk_35E;
    /* 0x0360 */ s16 unk_360;
    /* 0x0362 */ s16 unk_362;
    /* 0x0364 */ s16 unk_364;
    /* 0x0366 */ s16 unk_366;
    /* 0x0368 */ void* unk_368;
    /* 0x036C */ s32 unk_36C;
    /* 0x0370 */ UNK_TYPE1 unk370[4];
    /* 0x0374 */ s32 unk_374;
} EnJa; // size = 0x378

extern const ActorInit En_Ja_InitVars;

#endif // Z_EN_JA_H

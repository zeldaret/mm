#ifndef Z_EN_SELLNUTS_H
#define Z_EN_SELLNUTS_H

#include "global.h"

struct EnSellnuts;

typedef void (*EnSellnutsActionFunc)(struct EnSellnuts*, GlobalContext*);

#define ENSELLNUTS_GET_1(thisx) ((thisx)->params & 1)
#define ENSELLNUTS_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)

typedef struct EnSellnuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[28];
    /* 0x0230 */ Vec3s morphTable[28];
    /* 0x02D8 */ EnSellnutsActionFunc actionFunc;
    /* 0x02DC */ ColliderCylinder collider;
    /* 0x0328 */ s16 unk_328;
    /* 0x032C */ f32 unk_32C;
    /* 0x0330 */ Path* path;
    /* 0x0334 */ s32 unk_334;
    /* 0x0338 */ u16 unk_338;
    /* 0x033A */ u16 unk_33A;
    /* 0x033C */ s16 cutscene;
    /* 0x033E */ UNK_TYPE1 unk33E[0x2];
    /* 0x0340 */ u16 unk_340;
    /* 0x0342 */ u16 unk_342;
    /* 0x0344 */ s16 unk_344;
    /* 0x0346 */ UNK_TYPE1 unk346[0x4];
    /* 0x034A */ s16 unk_34A;
    /* 0x034C */ s16 unk_34C;
    /* 0x034E */ s16 unk_34E;
    /* 0x0350 */ s16 unk_350;
    /* 0x0354 */ f32 unk_354;
    /* 0x0358 */ f32 unk_358;
    /* 0x035C */ f32 unk_35C;
    /* 0x0360 */ f32 unk_360;
    /* 0x0364 */ s16 unk_364;
    /* 0x0366 */ s16 unk_366;
    /* 0x0368 */ s16 unk_368;
    /* 0x036A */ UNK_TYPE1 unk36A[0x2];
    /* 0x036C */ f32 unk_36C;
    /* 0x0370 */ f32 unk_370;
    /* 0x0374 */ f32 unk_374;
} EnSellnuts; // size = 0x378

extern const ActorInit En_Sellnuts_InitVars;

#endif // Z_EN_SELLNUTS_H

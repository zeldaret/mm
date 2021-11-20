#ifndef Z_EN_MUSHI2_H
#define Z_EN_MUSHI2_H

#include "global.h"

struct EnMushi2;

typedef void (*EnMushi2ActionFunc)(struct EnMushi2*, GlobalContext*);

#define ENMUSHI2_GET_3(thisx) ((thisx)->params & 3)

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
} EnMushi2Struct;

typedef struct EnMushi2 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[24];
    /* 0x0218 */ Vec3s morphTable[24];
    /* 0x02A8 */ ColliderJntSph collider;
    /* 0x02C8 */ ColliderJntSphElement colliderElements[1];
    /* 0x0308 */ EnMushi2ActionFunc actionFunc;
    /* 0x030C */ s32 unk_30C;
    /* 0x0310 */ Vec3f unk_310;
    /* 0x031C */ Vec3f unk_31C;
    /* 0x0328 */ Vec3f unk_328;
    /* 0x0334 */ CollisionPoly* unk_334;
    /* 0x0338 */ u32 unk_338;
    /* 0x033C */ Vec3f unk_33C;
    /* 0x0348 */ f32 unk_348;
    /* 0x034C */ struct ObjBean* unk_34C;
    /* 0x0350 */ f32 unk_350;
    /* 0x0354 */ f32 unk_354;
    /* 0x0358 */ f32 unk_358;
    /* 0x035C */ f32 unk_35C;
    /* 0x0360 */ f32 unk_360;
    /* 0x0364 */ s16 unk_364;
    /* 0x0366 */ s16 unk_366;
    /* 0x0368 */ s16 unk_368;
    /* 0x036A */ s16 unk_36A;
    /* 0x036C */ s16 unk_36C;
    /* 0x036E */ s16 unk_36E;
    /* 0x0370 */ s16 unk_370;
} EnMushi2; // size = 0x374

extern const ActorInit En_Mushi2_InitVars;

#endif // Z_EN_MUSHI2_H

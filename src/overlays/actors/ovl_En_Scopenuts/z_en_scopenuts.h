#ifndef Z_EN_SCOPENUTS_H
#define Z_EN_SCOPENUTS_H

#include "global.h"

struct EnScopenuts;

typedef void (*EnScopenutsActionFunc)(struct EnScopenuts*, GlobalContext*);

#define ENSCOPENUTS_GET_3E0(thisx) (((thisx)->params & 0x3E0) >> 5)
#define ENSCOPENUTS_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)

#define ENSCOPENUTS_3E0_0 0
#define ENSCOPENUTS_3E0_1 1

typedef struct EnScopenuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[28];
    /* 0x0230 */ Vec3s morphTable[28];
    /* 0x02D8 */ EnScopenutsActionFunc actionFunc;
    /* 0x02DC */ ColliderCylinder collider;
    /* 0x0328 */ u16 unk_328;
    /* 0x032C */ f32 unk_32C;
    /* 0x0330 */ Path* path;
    /* 0x0334 */ s32 unk_334;
    /* 0x0338 */ s16 unk_338;
    /* 0x033A */ UNK_TYPE1 unk33A[2];
    /* 0x033C */ u16 unk_33C;
    /* 0x033E */ s16 unk_33E;
    /* 0x0340 */ s16 unk_340;
    /* 0x0342 */ UNK_TYPE1 unk342[0x6];
    /* 0x0348 */ s32 unk_348;
    /* 0x034C */ s16 unk_34C;
    /* 0x034E */ s16 unk_34E;
    /* 0x0350 */ f32 unk_350;
    /* 0x0354 */ UNK_TYPE1 unk354[4];
    /* 0x0358 */ s16 unk_358;
    /* 0x035A */ s16 unk_35A;
    /* 0x035C */ f32 unk_35C;
    /* 0x0360 */ f32 unk_360;
    /* 0x0364 */ f32 unk_364;
    /* 0x0368 */ f32 unk_368;
    /* 0x036C */ s16 unk_36C;
    /* 0x036E */ s16 unk_36E;
    /* 0x0370 */ s16 unk_370;
    /* 0x0372 */ s16 unk_372;
} EnScopenuts; // size = 0x374

extern const ActorInit En_Scopenuts_InitVars;

#endif // Z_EN_SCOPENUTS_H

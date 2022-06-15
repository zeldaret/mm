#ifndef Z_EN_AKINDONUTS_H
#define Z_EN_AKINDONUTS_H

#include "global.h"

struct EnAkindonuts;

typedef void (*EnAkindonutsActionFunc)(struct EnAkindonuts*, GlobalContext*);
typedef void (*EnAkindonutsUnkFunc)(struct EnAkindonuts*, GlobalContext*);

#define ENAKINDONUTS_GET_3(thisx) ((thisx)->params & 3)
#define ENAKINDONUTS_GET_4(thisx) (((thisx)->params & 4) >> 2)
#define ENAKINDONUTS_GET_FC00(thisx) (((thisx)->params & 0xFC00) >> 0xA)

enum {
    /* 1 */ ENAKINDONUTS_3_1 = 1,
    /* 2 */ ENAKINDONUTS_3_2,
};

typedef struct EnAkindonuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[28];
    /* 0x0230 */ Vec3s morphTable[28];
    /* 0x02D8 */ EnAkindonutsActionFunc actionFunc;
    /* 0x02DC */ EnAkindonutsUnkFunc unk_2DC;
    /* 0x02E0 */ ColliderCylinder collider;
    /* 0x032C */ u16 unk_32C;
    /* 0x0330 */ Path* path;
    /* 0x0334 */ s32 unk_334;
    /* 0x0338 */ s16 unk_338;
    /* 0x033A */ s16 unk_33A;
    /* 0x033C */ u16 unk_33C;
    /* 0x033E */ s16 unk_33E;
    /* 0x0340 */ f32 unk_340;
    /* 0x0344 */ f32 unk_344;
    /* 0x0348 */ f32 unk_348;
    /* 0x034C */ f32 unk_34C;
    /* 0x0350 */ s16 unk_350;
    /* 0x0352 */ s16 unk_352;
    /* 0x0354 */ UNK_TYPE1 unk354[0x2];
    /* 0x0356 */ s16 unk_356;
    /* 0x0358 */ f32 unk_358;
    /* 0x035C */ s16 unk_35C;
    /* 0x035E */ s16 unk_35E;
    /* 0x0360 */ s16 cutscene;
    /* 0x0362 */ s16 unk_362;
    /* 0x0364 */ s16 unk_364;
    /* 0x0366 */ s8 unk_366;
    /* 0x0368 */ s16 unk_368;
} EnAkindonuts; // size = 0x36C

extern const ActorInit En_Akindonuts_InitVars;

#endif // Z_EN_AKINDONUTS_H

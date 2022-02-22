#ifndef Z_EN_OT_H
#define Z_EN_OT_H

#include "global.h"

struct EnOt;

typedef void (*EnOtActionFunc)(struct EnOt*, GlobalContext*);

#define ENOT_GET_7F(thisx) ((thisx)->params & 0x7F)
#define ENOT_GET_3F80(thisx) (((thisx)->params >> 7) & 0x7F)
#define ENOT_GET_3FFF(thisx) ((thisx)->params & 0x3FFF)
#define ENOT_GET_C000(thisx) (((thisx)->params >> 0xE) & 3)

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ UNK_TYPE1 unk_08[0x4];
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ UNK_TYPE1 unk_18[0x18];
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ UNK_TYPE1 unk_44[0x8];
    /* 0x4C */ u8 unk_4C;
    /* 0x50 */ Vec3f unk_50;
} EnOtUnkStruct; // size = 0x5C

typedef struct EnOt {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnOtActionFunc actionFunc;
    /* 0x0148 */ SkelAnime skelAnime;
    /* 0x018C */ ColliderCylinder collider;
    /* 0x01D8 */ Vec3s jointTable[19];
    /* 0x024A */ Vec3s morphTable[19];
    /* 0x02BC */ s32 animIdx;
    /* 0x02C0 */ ActorPathing actorPath;
    /* 0x032C */ u16 unk_32C;
    /* 0x0330 */ Vec3f unk_330;
    /* 0x033C */ s32 unk_33C;
    /* 0x0340 */ s32 unk_340;
    /* 0x0344 */ s16 unk_344;
    /* 0x0346 */ s16 unk_346;
    /* 0x0348 */ Vec3f unk_348;
    /* 0x0354 */ s16 unk_354;
    /* 0x0356 */ s16 cutscenes[4];
    /* 0x0360 */ struct EnOt* unk_360;
    /* 0x0364 */ LightNode* lightNode;
    /* 0x0368 */ LightInfo lightInfo;
    /* 0x0378 */ Vec3f unk_378;
    /* 0x0384 */ u8 unk_384;
    /* 0x0388 */ s32 unk_388;
    /* 0x038C */ s32 unk_38C;
    /* 0x0390 */ s16 unk_390;
    /* 0x0394 */ Vec3f unk_394;
    /* 0x03A0 */ s16 unk_3A0;
    /* 0x03A4 */ EnOtUnkStruct unk_3A4[10];
    /* 0x073C */ s16 unk_73C;
    /* 0x0740 */ f32 unk_740;
    /* 0x0744 */ Color_RGB8 unk_744;
    /* 0x0747 */ Color_RGB8 unk_747;
    /* 0x074C */ Vec3f unk_74C;
} EnOt; // size = 0x758

extern const ActorInit En_Ot_InitVars;

#endif // Z_EN_OT_H

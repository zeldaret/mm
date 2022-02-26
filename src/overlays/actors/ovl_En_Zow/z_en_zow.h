#ifndef Z_EN_ZOW_H
#define Z_EN_ZOW_H

#include "global.h"

struct EnZow;

typedef void (*EnZowActionFunc)(struct EnZow*, GlobalContext*);

#define ENZOW_GET_F(thisx) ((thisx)->params & 0xF)

#define ENZOW_F_1 1

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ UNK_TYPE1 unk_0C[0x3];
    /* 0x0F */ u8 unk_0F;
    /* 0x10 */ UNK_TYPE1 unk_10[0x4];
    /* 0x14 */ Vec3f unk_14;
    /* 0x20 */ Vec3f unk_20;
    /* 0x2C */ Vec3f unk_2C;
} EnZowStruct; // size = 0x38

typedef struct EnZow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ ColliderCylinder collider;
    /* 0x01D4 */ Vec3s jointTable[20];
    /* 0x024C */ Vec3s morphTable[20];
    /* 0x02C4 */ s16 unk_2C4;
    /* 0x02C6 */ s16 unk_2C6;
    /* 0x02C8 */ s16 unk_2C8;
    /* 0x02CA */ u16 unk_2CA;
    /* 0x02CC */ s16 unk_2CC;
    /* 0x02CE */ s16 unk_2CE;
    /* 0x02D0 */ EnZowStruct unk_2D0[15];
    /* 0x0618 */ EnZowActionFunc actionFunc;
} EnZow; // size = 0x61C

extern const ActorInit En_Zow_InitVars;

#endif // Z_EN_ZOW_H

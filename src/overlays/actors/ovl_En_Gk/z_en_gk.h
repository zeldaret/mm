#ifndef Z_EN_GK_H
#define Z_EN_GK_H

#include "global.h"

struct EnGk;

typedef void (*EnGkActionFunc)(struct EnGk*, GlobalContext*);

#define ENGK_GET_F(thisx) ((thisx)->params & 0xF)
#define ENGK_GET_F0(thisx) (((thisx)->params & 0xF0) >> 4)
#define ENGK_GET_3F00(thisx) (((thisx)->params & 0x3F00) >> 8)

enum {
    /* 0 */ ENGK_F_0,
    /* 1 */ ENGK_F_1,
    /* 2 */ ENGK_F_2,
    /* 3 */ ENGK_F_3,
    /* 4 */ ENGK_F_4,
    /* 5 */ ENGK_F_5,
};

typedef struct EnGk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder collider;
    /* 0x0190 */ SkelAnime skelAnime;
    /* 0x01D4 */ EnGkActionFunc actionFunc;
    /* 0x01D8 */ Vec3s unk_1D8;
    /* 0x01DE */ Vec3s unk_1DE;
    /* 0x01E4 */ u16 unk_1E4;
    /* 0x01E8 */ Path* path;
    /* 0x01EC */ s32 unk_1EC;
    /* 0x01F0 */ Vec3s jointTable[20];
    /* 0x01F0 */ Vec3s morphTable[20];
    /* 0x02E0 */ s16 unk_2E0;
    /* 0x02E2 */ s16 unk_2E2;
    /* 0x02E4 */ s16 unk_2E4;
    /* 0x02E8 */ Vec3f unk_2E8;
    /* 0x02F4 */ Vec3f unk_2F4;
    /* 0x0300 */ Vec3f unk_300;
    /* 0x030C */ Vec3f unk_30C;
    /* 0x0318 */ s16 unk_318;
    /* 0x031A */ u8 unk_31A;
    /* 0x031B */ u8 unk_31B;
    /* 0x031C */ u16 unk_31C;
    /* 0x031E */ s16 unk_31E;
    /* 0x0320 */ s16 unk_320;
    /* 0x0322 */ s16 unk_322;
    /* 0x0324 */ s16 unk_324;
    /* 0x0328 */ Vec3f unk_328;
    /* 0x0334 */ Vec3s unk_334;
    /* 0x033C */ Vec3f unk_33C;
    /* 0x0348 */ Vec3s unk_348;
    /* 0x034E */ s16 unk_34E;
    /* 0x0350 */ s16 unk_350;
    /* 0x0354 */ f32 unk_354;
} EnGk; // size = 0x358

extern const ActorInit En_Gk_InitVars;

#endif // Z_EN_GK_H

#ifndef Z_EN_AOB_01_H
#define Z_EN_AOB_01_H

#include "global.h"
#include "objects/object_aob/object_aob.h"

struct EnAob01;

typedef void (*EnAob01ActionFunc)(struct EnAob01*, GlobalContext*);

#define ENAOB01_GET_7E00_1(thisx) ((thisx)->params & 0x7E00)
#define ENAOB01_GET_7E00_2(thisx) (((thisx)->params & 0x7E00) >> 9)

typedef struct EnAob01 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnAob01ActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Path* unk_1D8[14];
    /* 0x210 */ u16 unk_210;
    /* 0x212 */ Vec3s jointTable[MAMAMU_YAN_LIMB_MAX];
    /* 0x272 */ Vec3s morphTable[MAMAMU_YAN_LIMB_MAX];
    /* 0x2D2 */ u16 unk_2D2;
    /* 0x2D4 */ Vec3s unk_2D4;
    /* 0x2DA */ Vec3s unk_2DA;
    /* 0x2E0 */ Vec3s unk_2E0;
    /* 0x2E6 */ Vec3s unk_2E6;
    /* 0x2EC */ Vec3s unk_2EC;
    /* 0x2F2 */ Vec3s unk_2F2;
    /* 0x2F8 */ s16 unk_2F8[MAMAMU_YAN_LIMB_MAX];
    /* 0x318 */ s16 unk_318[MAMAMU_YAN_LIMB_MAX];
    /* 0x338 */ UNK_TYPE1 unk338[0xB6];
    /* 0x3EE */ s16 eyeIndex;
    /* 0x3F0 */ s16 blinkTimer;
    /* 0x3F4 */ Actor* unk_3F4;
    /* 0x3F8 */ Actor* unk_3F8[14];
    /* 0x430 */ s16 unk_430;
    /* 0x432 */ s16 unk_432;
    /* 0x434 */ s32 unk_434;
    /* 0x438 */ UNK_TYPE1 unk438[4];
    /* 0x43C */ s32 unk_43C;
    /* 0x440 */ s16 unk_440;
} EnAob01; // size = 0x444

extern const ActorInit En_Aob_01_InitVars;

#endif // Z_EN_AOB_01_H

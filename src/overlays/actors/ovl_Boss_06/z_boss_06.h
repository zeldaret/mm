#ifndef Z_BOSS_06_H
#define Z_BOSS_06_H

#include "global.h"

struct Boss06;

typedef void (*Boss06ActionFunc)(struct Boss06*, PlayState*);

#define ENBOSS06_GET_PARAMS(thisx) ((thisx)->params)

typedef struct Boss06 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u8 unk_144;
    /* 0x146 */ s16 unk_146;
    /* 0x148 */ s16 unk_148;
    /* 0x14C */ ColliderCylinder collider;
    /* 0x198 */ Boss06ActionFunc actionFunc;
    /* 0x19C */ f32 unk_19C;
    /* 0x1A0 */ f32 unk_1A0;
    /* 0x1A4 */ f32 unk_1A4;
    /* 0x1A8 */ f32 unk_1A8;
    /* 0x1AC */ f32 unk_1AC;
    /* 0x1B0 */ f32 unk_1B0;
    /* 0x1B4 */ f32 unk_1B4;
    /* 0x1B8 */ UNK_TYPE1 unk1B8[4];
    /* 0x1BC */ f32 unk_1BC;
    /* 0x1C0 */ f32 unk_1C0;
    /* 0x1C4 */ UNK_TYPE1 unk1C4[4];
    /* 0x1C8 */ u8 unk_1C8;
    /* 0x1C9 */ u8 unk_1C9;
    /* 0x1CA */ s16 unk_1CA;
    /* 0x1CC */ f32 unk_1CC;
    /* 0x1D0 */ f32 unk_1D0;
    /* 0x1D4 */ f32 unk_1D4;
    /* 0x1D8 */ f32 unk_1D8;
    /* 0x1DC */ f32 unk_1DC;
    /* 0x1E0 */ f32 unk_1E0;
    /* 0x1E4 */ f32 unk_1E4;
    /* 0x1E8 */ UNK_TYPE1 unk1E8[0x15];
    /* 0x1FD */ u8 unk_1FD;
    /* 0x1FE */ u8 unk_1FE;
    /* 0x1FF */ u8 unk_1FF;
    /* 0x200 */ u8 unk_200[0x800];
    /* 0xA00 */ s16 subCamId;
    /* 0xA04 */ Vec3f subCamEye;
    /* 0xA10 */ Vec3f subCamAt;
    /* 0xA1C */ Vec3f unk_A1C;
    /* 0xA28 */ f32 unk_A28;
    /* 0xA2C */ f32 unk_A2C;
} Boss06; // size = 0xA30

#endif // Z_BOSS_06_H

#ifndef Z_BOSS_06_H
#define Z_BOSS_06_H

#include "global.h"

struct Boss06;

typedef void (*Boss06ActionFunc)(struct Boss06*, GlobalContext*);

#define ENBOSS06_GET_PARAMS(thisx) ((thisx)->params)

typedef struct Boss06 {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ u8 unk_144;
    /* 0x0146 */ s16 unk_146;
    /* 0x0148 */ s16 unk_148;
    /* 0x014C */ ColliderCylinder collider;
    /* 0x0198 */ Boss06ActionFunc actionFunc;
    /* 0x019C */ f32 unk_19C;
    /* 0x01A0 */ f32 unk_1A0;
    /* 0x01A4 */ f32 unk_1A4;
    /* 0x01A8 */ f32 unk_1A8;
    /* 0x01AC */ f32 unk_1AC;
    /* 0x01B0 */ f32 unk_1B0;
    /* 0x01B4 */ f32 unk_1B4;
    /* 0x01B8 */ UNK_TYPE1 unk1B8[4];
    /* 0x01BC */ f32 unk_1BC;
    /* 0x01C0 */ f32 unk_1C0;
    /* 0x01C4 */ UNK_TYPE1 unk1C4[4];
    /* 0x01C8 */ u8 unk_1C8;
    /* 0x01C9 */ u8 unk_1C9;
    /* 0x01CA */ s16 unk_1CA;
    /* 0x01CC */ f32 unk_1CC;
    /* 0x01D0 */ f32 unk_1D0;
    /* 0x01D4 */ f32 unk_1D4;
    /* 0x01D8 */ f32 unk_1D8;
    /* 0x01DC */ f32 unk_1DC;
    /* 0x01E0 */ f32 unk_1E0;
    /* 0x01E4 */ f32 unk_1E4;
    /* 0x01E8 */ UNK_TYPE1 unk1E8[0x15];
    /* 0x01FD */ u8 unk_1FD;
    /* 0x01FE */ u8 unk_1FE;
    /* 0x01FF */ u8 unk_1FF;
    /* 0x0200 */ u8 unk_200[0x800];
    /* 0x0A00 */ s16 unk_A00;
    /* 0x0A04 */ Vec3f unk_A04;
    /* 0x0A10 */ Vec3f unk_A10;
    /* 0x0A1C */ Vec3f unk_A1C;
    /* 0x0A28 */ f32 unk_A28;
    /* 0x0A2C */ f32 unk_A2C;
} Boss06; // size = 0xA30

extern const ActorInit Boss_06_InitVars;

#endif // Z_BOSS_06_H

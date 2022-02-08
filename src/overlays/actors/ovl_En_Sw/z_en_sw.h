#ifndef Z_EN_SW_H
#define Z_EN_SW_H

#include "global.h"

struct EnSw;

typedef void (*EnSwActionFunc)(struct EnSw*, GlobalContext*);

#define ENSW_GET_3(thisx) (((thisx)->params & 3) & 0xFF)
#define ENSW_GET_3FC(thisx) (((thisx)->params & 0x3FC) >> 2)
#define ENSW_GET_FF00(thisx) ((((thisx)->params & 0xFF00) >> 8) & 0xFF)

typedef struct EnSw {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ EnSwActionFunc actionFunc;
    /* 0x018C */ ColliderSphere collider;
    /* 0x01E4 */ Path* unk_1E4;
    /* 0x01E8 */ Vec3s jointTable[30];
    /* 0x029C */ Vec3s morphTable[30];
    /* 0x0350 */ Vec3f unk_350;
    /* 0x035C */ Vec3f unk_35C;
    /* 0x0368 */ Vec3f unk_368;
    /* 0x0374 */ Vec3f unk_374;
    /* 0x0380 */ Vec3f unk_380[12];
    /* 0x0410 */ u16 unk_410;
    /* 0x0412 */ u8 drawDmgEffType;
    /* 0x0414 */ f32 unk_414;
    /* 0x0418 */ f32 drawDmgEffFrozenSteamScales[12];
    /* 0x0448 */ f32 unk_448;
    /* 0x044C */ f32 unk_44C;
    /* 0x0450 */ f32 unk_450;
    /* 0x0454 */ s16 unk_454;
    /* 0x0456 */ s16 unk_456;
    /* 0x0458 */ s16 unk_458;
    /* 0x045A */ s16 unk_45A;
    /* 0x045C */ s16 unk_45C;
    /* 0x045E */ s16 unk_45E;
    /* 0x0460 */ s16 unk_460;
    /* 0x0462 */ s16 unk_462;
    /* 0x0464 */ s16 unk_464[12];
    /* 0x047C */ s16 unk_47C[12];
    /* 0x0494 */ s16 unk_494;
    /* 0x0496 */ s16 unk_496;
    /* 0x0498 */ s16 unk_498;
    /* 0x049C */ s32 unk_49C;
    /* 0x04A0 */ s32 unk_4A0;
} EnSw; // size = 0x4A4

extern const ActorInit En_Sw_InitVars;

#endif // Z_EN_SW_H

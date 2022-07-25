#ifndef Z_EN_SW_H
#define Z_EN_SW_H

#include "global.h"

struct EnSw;

typedef void (*EnSwActionFunc)(struct EnSw*, PlayState*);

#define ENSW_GETS_3(params) ((params & 3) & 0xFF)
#define ENSW_GET_3(thisx) (ENSW_GETS_3((thisx)->params))
#define ENSW_GETS_3FC(params) (((params & 0x3FC) >> 2) & 0xFF)
#define ENSW_GET_3FC(thisx) (ENSW_GETS_3FC((thisx)->params))
#define ENSW_GET_FF00(thisx) ((((thisx)->params & 0xFF00) >> 8) & 0xFF)

typedef struct EnSw {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnSwActionFunc actionFunc;
    /* 0x18C */ ColliderSphere collider;
    /* 0x1E4 */ Path* unk_1E4;
    /* 0x1E8 */ Vec3s jointTable[30];
    /* 0x29C */ Vec3s morphTable[30];
    /* 0x350 */ Vec3f unk_350;
    /* 0x35C */ Vec3f unk_35C;
    /* 0x368 */ Vec3f unk_368;
    /* 0x374 */ Vec3f unk_374;
    /* 0x380 */ Vec3f unk_380[12];
    /* 0x410 */ u16 unk_410;
    /* 0x412 */ u8 drawDmgEffType;
    /* 0x414 */ f32 unk_414;
    /* 0x418 */ f32 drawDmgEffFrozenSteamScales[12];
    /* 0x448 */ f32 unk_448;
    /* 0x44C */ f32 unk_44C;
    /* 0x450 */ f32 unk_450;
    /* 0x454 */ s16 unk_454;
    /* 0x456 */ s16 unk_456;
    /* 0x458 */ s16 unk_458;
    /* 0x45A */ s16 unk_45A;
    /* 0x45C */ s16 unk_45C;
    /* 0x45E */ s16 unk_45E;
    /* 0x460 */ s16 unk_460;
    /* 0x462 */ s16 unk_462;
    /* 0x464 */ s16 unk_464[12];
    /* 0x47C */ s16 unk_47C[12];
    /* 0x494 */ s16 unk_494;
    /* 0x496 */ s16 unk_496;
    /* 0x498 */ s16 unk_498;
    /* 0x49C */ s32 unk_49C;
    /* 0x4A0 */ s32 unk_4A0;
} EnSw; // size = 0x4A4

extern const ActorInit En_Sw_InitVars;

#endif // Z_EN_SW_H

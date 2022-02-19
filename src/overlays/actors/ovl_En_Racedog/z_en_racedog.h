#ifndef Z_EN_RACEDOG_H
#define Z_EN_RACEDOG_H

#include "global.h"

struct EnRacedog;

typedef void (*EnRacedogActionFunc)(struct EnRacedog*, GlobalContext*);

typedef struct EnRacedog {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnRacedogActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x4];
    /* 0x14C */ SkelAnime skelAnime;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ char unk_1DC[0xC];
    /* 0x1E8 */ s32 unk_1E8;
    /* 0x1EC */ char unk_1EC[0x9C];
    /* 0x288 */ s16 unk_288;
    /* 0x28A */ char unk_28A[0x6];
    /* 0x290 */ s16 unk_290;
    /* 0x292 */ s16 unk_292;
    /* 0x294 */ char unk_294[0x8];
    /* 0x29C */ s16 unk_29C;
    /* 0x29E */ char unk_29E[0xE];
    /* 0x2AC */ f32 unk_2AC;
    /* 0x2B0 */ char unk_2B0[0xC];
    /* 0x2BC */ s32 unk_2BC;
    /* 0x2C0 */ s32 unk_2C0;
    /* 0x2C4 */ f32 unk_2C4;
} EnRacedog; // size = 0x2C8

extern const ActorInit En_Racedog_InitVars;

#endif // Z_EN_RACEDOG_H

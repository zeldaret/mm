#ifndef Z_BG_LOTUS_H
#define Z_BG_LOTUS_H

#include "global.h"

struct BgLotus;

typedef struct BgLotus {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ s32 unk15C;
    /* 0x160 */ f32 unk160;
    /* 0x164 */ u8 unk164;
    /* 0x166 */ s16 unk166;
    /* 0x168 */ s16 unk168;
    /* 0x16A */ char pad16A[2];
} BgLotus; /* size = 0x16C */

#endif // Z_BG_LOTUS_H

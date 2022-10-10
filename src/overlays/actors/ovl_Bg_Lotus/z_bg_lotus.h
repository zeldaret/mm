#ifndef Z_BG_LOTUS_H
#define Z_BG_LOTUS_H

#include "global.h"

struct BgLotus;

typedef void (*BgLotusActionFunc)(struct BgLotus* this, PlayState* play);

typedef struct BgLotus {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgLotusActionFunc actionFunc;
    /* 0x160 */ f32 unk_160;
    /* 0x164 */ u8 unk_164;
    /* 0x166 */ s16 unk_166;
    /* 0x168 */ s16 unk_168;
} BgLotus; // size = 0x16C

#endif // Z_BG_LOTUS_H

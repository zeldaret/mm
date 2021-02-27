#ifndef Z_BG_LOTUS_H
#define Z_BG_LOTUS_H

#include <global.h>

struct BgLotus;

typedef void (*BgLotusActionFunc)(struct BgLotus*, GlobalContext*);

typedef struct BgLotus {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgLotusActionFunc actionFunc;
    /* 0x160 */ f32 unk160;
    /* 0x164 */ u8 unk164;
    /* 0x166 */ s16 timer;
    /* 0x168 */ s16 timer2;
} BgLotus; // size = 0x16C

extern const ActorInit Bg_Lotus_InitVars;

#endif // Z_BG_LOTUS_H

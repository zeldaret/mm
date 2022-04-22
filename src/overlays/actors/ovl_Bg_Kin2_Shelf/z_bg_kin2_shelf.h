#ifndef Z_BG_KIN2_SHELF_H
#define Z_BG_KIN2_SHELF_H

#include "global.h"

struct BgKin2Shelf;

typedef void (*BgKin2ShelfActionFunc)(struct BgKin2Shelf*, GlobalContext*);

#define BGKIN2SHELF_GET_1(thisx) ((thisx)->params & 1)

typedef struct BgKin2Shelf {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x015C */ BgKin2ShelfActionFunc actionFunc;
    /* 0x0160 */ f32 unk_160;
    /* 0x0164 */ u8 unk_164;
    /* 0x0165 */ s8 unk_165;
    /* 0x0166 */ s8 unk_166;
    /* 0x0167 */ s8 unk_167;
} BgKin2Shelf; // size = 0x168

extern const ActorInit Bg_Kin2_Shelf_InitVars;

#endif // Z_BG_KIN2_SHELF_H

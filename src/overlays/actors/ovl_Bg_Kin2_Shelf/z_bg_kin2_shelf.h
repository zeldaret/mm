#ifndef Z_BG_KIN2_SHELF_H
#define Z_BG_KIN2_SHELF_H

#include "global.h"

struct BgKin2Shelf;

typedef void (*BgKin2ShelfActionFunc)(struct BgKin2Shelf*, GlobalContext*);

typedef struct BgKin2Shelf {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgKin2ShelfActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x8];
} BgKin2Shelf; // size = 0x168

extern const ActorInit Bg_Kin2_Shelf_InitVars;

#endif // Z_BG_KIN2_SHELF_H

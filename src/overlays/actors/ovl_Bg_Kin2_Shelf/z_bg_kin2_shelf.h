#ifndef Z_BG_KIN2_SHELF_H
#define Z_BG_KIN2_SHELF_H

#include <global.h>

struct BgKin2Shelf;

typedef struct BgKin2Shelf {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} BgKin2Shelf; // size = 0x168

extern const ActorInit Bg_Kin2_Shelf_InitVars;

#endif // Z_BG_KIN2_SHELF_H

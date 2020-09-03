#ifndef Z_BG_CTOWER_GEAR_H
#define Z_BG_CTOWER_GEAR_H

#include <global.h>

struct BgCtowerGear;

typedef struct BgCtowerGear {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
} BgCtowerGear; // size = 0x15C

extern const ActorInit Bg_Ctower_Gear_InitVars;

#endif // Z_BG_CTOWER_GEAR_H

#ifndef Z_BG_KIN2_BOMBWALL_H
#define Z_BG_KIN2_BOMBWALL_H

#include "global.h"

struct BgKin2Bombwall;

typedef void (*BgKin2BombwallActionFunc)(struct BgKin2Bombwall*, GlobalContext*);

typedef struct BgKin2Bombwall {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x64];
    /* 0x01A8 */ BgKin2BombwallActionFunc actionFunc;
    /* 0x01AC */ char unk_1AC[0x4];
} BgKin2Bombwall; // size = 0x1B0

extern const ActorInit Bg_Kin2_Bombwall_InitVars;

#endif // Z_BG_KIN2_BOMBWALL_H

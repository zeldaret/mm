#ifndef Z_BG_DBLUE_BALANCE_H
#define Z_BG_DBLUE_BALANCE_H

#include <global.h>

struct BgDblueBalance;

typedef struct BgDblueBalance {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xE8];
} BgDblueBalance; // size = 0x22C

extern const ActorInit Bg_Dblue_Balance_InitVars;

#endif // Z_BG_DBLUE_BALANCE_H

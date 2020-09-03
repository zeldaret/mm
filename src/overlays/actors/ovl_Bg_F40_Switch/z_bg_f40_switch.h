#ifndef _Z_BG_F40_SWITCH_H_
#define _Z_BG_F40_SWITCH_H_

#include <global.h>

struct BgF40Switch;

typedef struct BgF40Switch {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} BgF40Switch; // size = 0x168

extern const ActorInit Bg_F40_Switch_InitVars;

#endif

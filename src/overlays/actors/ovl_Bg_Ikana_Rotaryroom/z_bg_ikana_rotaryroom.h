#ifndef _Z_BG_IKANA_ROTARYROOM_H_
#define _Z_BG_IKANA_ROTARYROOM_H_

#include <global.h>

struct BgIkanaRotaryroom;

typedef struct BgIkanaRotaryroom {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x444];
} BgIkanaRotaryroom; // size = 0x588

extern const ActorInit Bg_Ikana_Rotaryroom_InitVars;

#endif

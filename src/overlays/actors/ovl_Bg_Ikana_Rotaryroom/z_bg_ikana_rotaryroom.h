#ifndef Z_BG_IKANA_ROTARYROOM_H
#define Z_BG_IKANA_ROTARYROOM_H

#include "global.h"

struct BgIkanaRotaryroom;

typedef void (*BgIkanaRotaryroomActionFunc)(struct BgIkanaRotaryroom*, GlobalContext*);

typedef struct BgIkanaRotaryroom {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x43C];
    /* 0x0580 */ BgIkanaRotaryroomActionFunc actionFunc;
    /* 0x0584 */ char unk_584[0x4];
} BgIkanaRotaryroom; // size = 0x588

extern const ActorInit Bg_Ikana_Rotaryroom_InitVars;

#endif // Z_BG_IKANA_ROTARYROOM_H

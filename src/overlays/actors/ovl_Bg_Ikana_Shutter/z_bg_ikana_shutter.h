#ifndef _Z_BG_IKANA_SHUTTER_H_
#define _Z_BG_IKANA_SHUTTER_H_

#include <global.h>

struct BgIkanaShutter;

typedef struct BgIkanaShutter {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C];
} BgIkanaShutter; // size = 0x160

extern const ActorInit Bg_Ikana_Shutter_InitVars;

#endif

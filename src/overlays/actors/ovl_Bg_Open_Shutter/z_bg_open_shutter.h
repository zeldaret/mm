#ifndef Z_BG_OPEN_SHUTTER_H
#define Z_BG_OPEN_SHUTTER_H

#include <global.h>

struct BgOpenShutter;

typedef struct BgOpenShutter {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x24];
} BgOpenShutter; // size = 0x168

extern const ActorInit Bg_Open_Shutter_InitVars;

#endif // Z_BG_OPEN_SHUTTER_H

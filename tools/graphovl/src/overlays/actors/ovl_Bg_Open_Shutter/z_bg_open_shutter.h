#ifndef Z_BG_OPEN_SHUTTER_H
#define Z_BG_OPEN_SHUTTER_H

#include "global.h"

struct BgOpenShutter;

typedef void (*BgOpenShutterActionFunc)(struct BgOpenShutter*, GlobalContext*);

typedef struct BgOpenShutter {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C];
    /* 0x0160 */ BgOpenShutterActionFunc actionFunc;
    /* 0x0164 */ char unk_164[0x4];
} BgOpenShutter; // size = 0x168

extern const ActorInit Bg_Open_Shutter_InitVars;

#endif // Z_BG_OPEN_SHUTTER_H

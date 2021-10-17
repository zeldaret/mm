#ifndef Z_BG_IKANA_SHUTTER_H
#define Z_BG_IKANA_SHUTTER_H

#include "global.h"

struct BgIkanaShutter;

typedef void (*BgIkanaShutterActionFunc)(struct BgIkanaShutter*, GlobalContext*);

typedef struct BgIkanaShutter {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgIkanaShutterActionFunc actionFunc;
} BgIkanaShutter; // size = 0x160

extern const ActorInit Bg_Ikana_Shutter_InitVars;

#endif // Z_BG_IKANA_SHUTTER_H

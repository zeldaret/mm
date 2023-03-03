#ifndef Z_BG_IKANA_SHUTTER_H
#define Z_BG_IKANA_SHUTTER_H

#include "global.h"

struct BgIkanaShutter;

typedef void (*BgIkanaShutterActionFunc)(struct BgIkanaShutter*, PlayState*);

typedef struct BgIkanaShutter {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgIkanaShutterActionFunc actionFunc;
} BgIkanaShutter; // size = 0x160

#endif // Z_BG_IKANA_SHUTTER_H

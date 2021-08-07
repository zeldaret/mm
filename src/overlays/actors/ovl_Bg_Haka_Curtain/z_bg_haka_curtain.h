#ifndef Z_BG_HAKA_CURTAIN_H
#define Z_BG_HAKA_CURTAIN_H

#include "global.h"

struct BgHakaCurtain;

typedef void (*BgHakaCurtainActionFunc)(struct BgHakaCurtain*, GlobalContext*);

typedef struct BgHakaCurtain {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ BgHakaCurtainActionFunc actionFunc;
} BgHakaCurtain; // size = 0x160

extern const ActorInit Bg_Haka_Curtain_InitVars;

#endif // Z_BG_HAKA_CURTAIN_H

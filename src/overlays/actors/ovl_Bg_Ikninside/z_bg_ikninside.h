#ifndef Z_BG_IKNINSIDE_H
#define Z_BG_IKNINSIDE_H

#include "global.h"

struct BgIkninside;

typedef void (*BgIkninsideActionFunc)(struct BgIkninside*, GlobalContext*);

typedef struct BgIkninside {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x68];
    /* 0x01AC */ BgIkninsideActionFunc actionFunc;
} BgIkninside; // size = 0x1B0

extern const ActorInit Bg_Ikninside_InitVars;

#endif // Z_BG_IKNINSIDE_H

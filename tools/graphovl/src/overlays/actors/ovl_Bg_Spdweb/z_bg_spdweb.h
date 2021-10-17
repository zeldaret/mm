#ifndef Z_BG_SPDWEB_H
#define Z_BG_SPDWEB_H

#include "global.h"

struct BgSpdweb;

typedef void (*BgSpdwebActionFunc)(struct BgSpdweb*, GlobalContext*);

typedef struct BgSpdweb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgSpdwebActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x19C];
} BgSpdweb; // size = 0x2FC

extern const ActorInit Bg_Spdweb_InitVars;

#endif // Z_BG_SPDWEB_H

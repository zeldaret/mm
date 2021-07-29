#ifndef Z_BG_SINKAI_KABE_H
#define Z_BG_SINKAI_KABE_H

#include "global.h"

struct BgSinkaiKabe;

typedef void (*BgSinkaiKabeActionFunc)(struct BgSinkaiKabe* this, GlobalContext* globalCtx);

typedef struct BgSinkaiKabe {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgSinkaiKabeActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x10];
} BgSinkaiKabe; // size = 0x170

extern const ActorInit Bg_Sinkai_Kabe_InitVars;

#endif // Z_BG_SINKAI_KABE_H

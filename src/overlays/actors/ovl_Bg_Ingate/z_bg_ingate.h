#ifndef Z_BG_INGATE_H
#define Z_BG_INGATE_H

#include "global.h"

struct BgIngate;

typedef void (*BgIngateActionFunc)(struct BgIngate* this, GlobalContext* globalCtx);

typedef struct BgIngate {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x18];
    /* 0x015C */ BgIngateActionFunc actionFunc;
    /* 0x0160 */ char unk_160[0x30];
} BgIngate; // size = 0x190

extern const ActorInit Bg_Ingate_InitVars;

#endif // Z_BG_INGATE_H

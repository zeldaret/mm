#ifndef Z_BG_BOTIHASIRA_H
#define Z_BG_BOTIHASIRA_H

#include "global.h"

struct BgBotihasira;

typedef void (*BgBotihasiraActionFunc)(struct BgBotihasira*, PlayState*);

typedef struct BgBotihasira {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
    /* 0x15C */ BgBotihasiraActionFunc actionFunc;
    /* 0x160 */ char unk_160[0x4C];
} BgBotihasira; // size = 0x1AC

extern const ActorInit Bg_Botihasira_InitVars;

#endif // Z_BG_BOTIHASIRA_H

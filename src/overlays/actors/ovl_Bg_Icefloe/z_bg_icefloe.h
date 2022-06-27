#ifndef Z_BG_ICEFLOE_H
#define Z_BG_ICEFLOE_H

#include "global.h"

struct BgIcefloe;

typedef void (*BgIcefloeActionFunc)(struct BgIcefloe*, PlayState*);

typedef struct BgIcefloe {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
    /* 0x15C */ BgIcefloeActionFunc actionFunc;
    /* 0x160 */ char unk_160[0x4];
} BgIcefloe; // size = 0x164

extern const ActorInit Bg_Icefloe_InitVars;

#endif // Z_BG_ICEFLOE_H

#ifndef _Z_BG_ICEFLOE_H_
#define _Z_BG_ICEFLOE_H_

#include <global.h>

struct BgIcefloe;

typedef struct BgIcefloe {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x20];
} BgIcefloe; // size = 0x164

extern const ActorInit Bg_Icefloe_InitVars;

#endif

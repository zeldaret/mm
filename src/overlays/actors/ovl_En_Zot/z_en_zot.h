#ifndef _Z_EN_ZOT_H_
#define _Z_EN_ZOT_H_

#include <global.h>

struct EnZot;

typedef struct EnZot {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1B8];
} EnZot; // size = 0x2FC

extern const ActorInit En_Zot_InitVars;

#endif

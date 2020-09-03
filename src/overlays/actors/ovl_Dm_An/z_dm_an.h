#ifndef _Z_DM_AN_H_
#define _Z_DM_AN_H_

#include <global.h>

struct DmAn;

typedef struct DmAn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x194];
} DmAn; // size = 0x2D8

extern const ActorInit Dm_An_InitVars;

#endif

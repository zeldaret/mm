#ifndef _Z_DM_GM_H_
#define _Z_DM_GM_H_

#include <global.h>

struct DmGm;

typedef struct DmGm {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x194];
} DmGm; // size = 0x2D8

extern const ActorInit Dm_Gm_InitVars;

#endif

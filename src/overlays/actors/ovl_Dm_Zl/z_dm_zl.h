#ifndef Z_DM_ZL_H
#define Z_DM_ZL_H

#include <global.h>

struct DmZl;

typedef struct DmZl {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x190];
} DmZl; // size = 0x2D4

extern const ActorInit Dm_Zl_InitVars;

#endif // Z_DM_ZL_H

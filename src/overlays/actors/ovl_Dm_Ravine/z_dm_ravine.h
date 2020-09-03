#ifndef Z_DM_RAVINE_H
#define Z_DM_RAVINE_H

#include <global.h>

struct DmRavine;

typedef struct DmRavine {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x8];
} DmRavine; // size = 0x14C

extern const ActorInit Dm_Ravine_InitVars;

#endif // Z_DM_RAVINE_H

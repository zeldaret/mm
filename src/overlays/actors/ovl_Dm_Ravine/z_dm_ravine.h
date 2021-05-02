#ifndef Z_DM_RAVINE_H
#define Z_DM_RAVINE_H

#include <global.h>

struct DmRavine;

typedef struct DmRavine {
    /* 0x000 */ Actor actor;
    /* 0x144 */ void (*actionFunc)(Actor*, GlobalContext*); // unused
    /* 0x148 */ u8 state;
    /* 0x149 */ u8 loaded;
    /* 0x14a */ u8 pad_14a[2];
} DmRavine; // size = 0x14C

extern const ActorInit Dm_Ravine_InitVars;

#endif // Z_DM_RAVINE_H

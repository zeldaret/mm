#ifndef Z_DM_RAVINE_H
#define Z_DM_RAVINE_H

#include <global.h>

struct DmRavine;

typedef void (*DmRavineActionFunc)(struct DmRavine*, GlobalContext*);

typedef struct DmRavine {
    /* 0x000 */ Actor actor;
    /* 0x144 */ DmRavineActionFunc actionFunc;
    /* 0x148 */ u8 state;
    /* 0x149 */ u8 loaded;
    /* 0x14A */ u8 pad_14A[2];
} DmRavine; // size = 0x14C

extern const ActorInit Dm_Ravine_InitVars;

#endif // Z_DM_RAVINE_H

#ifndef _Z_DM_OPSTAGE_H_
#define _Z_DM_OPSTAGE_H_

#include <global.h>

struct DmOpstage;

typedef struct DmOpstage {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} DmOpstage; // size = 0x1B0

extern const ActorInit Dm_Opstage_InitVars;

#endif

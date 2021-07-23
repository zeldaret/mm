#ifndef Z_DM_CHAR00_H
#define Z_DM_CHAR00_H

#include "global.h"

struct DmChar00;

typedef struct DmChar00 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x120];
} DmChar00; // size = 0x264

extern const ActorInit Dm_Char00_InitVars;

#endif // Z_DM_CHAR00_H

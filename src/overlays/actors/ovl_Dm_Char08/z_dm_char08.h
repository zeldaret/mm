#ifndef Z_DM_CHAR08_H
#define Z_DM_CHAR08_H

#include "global.h"

struct DmChar08;

typedef struct DmChar08 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC8];
} DmChar08; // size = 0x20C

extern const ActorInit Dm_Char08_InitVars;

#endif // Z_DM_CHAR08_H

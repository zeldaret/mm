#ifndef Z_DM_CHAR02_H
#define Z_DM_CHAR02_H

#include "global.h"

struct DmChar02;

typedef struct DmChar02 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1B0];
} DmChar02; // size = 0x2F4

extern const ActorInit Dm_Char02_InitVars;

#endif // Z_DM_CHAR02_H

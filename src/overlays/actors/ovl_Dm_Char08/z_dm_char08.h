#ifndef Z_DM_CHAR08_H
#define Z_DM_CHAR08_H

#include "global.h"

struct DmChar08;

typedef void (*DmChar08ActionFunc)(struct DmChar08*, PlayState*);

typedef struct DmChar08 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x5C];
    /* 0x1A0 */ DmChar08ActionFunc actionFunc;
    /* 0x1A4 */ char unk_1A4[0x68];
} DmChar08; // size = 0x20C

extern const ActorInit Dm_Char08_InitVars;

#endif // Z_DM_CHAR08_H

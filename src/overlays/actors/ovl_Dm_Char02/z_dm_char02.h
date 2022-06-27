#ifndef Z_DM_CHAR02_H
#define Z_DM_CHAR02_H

#include "global.h"

struct DmChar02;

typedef void (*DmChar02ActionFunc)(struct DmChar02*, PlayState*);

typedef struct DmChar02 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x14C];
    /* 0x290 */ DmChar02ActionFunc actionFunc;
    /* 0x294 */ char unk_294[0x60];
} DmChar02; // size = 0x2F4

extern const ActorInit Dm_Char02_InitVars;

#endif // Z_DM_CHAR02_H

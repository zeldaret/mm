#ifndef Z_DM_AN_H
#define Z_DM_AN_H

#include "global.h"

struct DmAn;

typedef void (*DmAnActionFunc)(struct DmAn*, GlobalContext*);

typedef struct DmAn {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ DmAnActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x14C];
} DmAn; // size = 0x2D8

extern const ActorInit Dm_An_InitVars;

#endif // Z_DM_AN_H

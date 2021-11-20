#ifndef Z_DM_OPSTAGE_H
#define Z_DM_OPSTAGE_H

#include "global.h"

struct DmOpstage;

typedef void (*DmOpstageActionFunc)(struct DmOpstage*, GlobalContext*);

typedef struct DmOpstage {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x5C];
    /* 0x01A0 */ DmOpstageActionFunc actionFunc;
    /* 0x01A4 */ char unk_1A4[0xC];
} DmOpstage; // size = 0x1B0

extern const ActorInit Dm_Opstage_InitVars;

#endif // Z_DM_OPSTAGE_H

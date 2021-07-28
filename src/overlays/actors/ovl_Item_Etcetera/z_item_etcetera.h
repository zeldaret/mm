#ifndef Z_ITEM_ETCETERA_H
#define Z_ITEM_ETCETERA_H

#include "global.h"

struct ItemEtcetera;

typedef struct ItemEtcetera {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x14];
} ItemEtcetera; // size = 0x158

extern const ActorInit Item_Etcetera_InitVars;

#endif // Z_ITEM_ETCETERA_H

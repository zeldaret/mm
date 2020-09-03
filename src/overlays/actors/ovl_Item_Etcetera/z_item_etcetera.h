#ifndef _Z_ITEM_ETCETERA_H_
#define _Z_ITEM_ETCETERA_H_

#include <global.h>

struct ItemEtcetera;

typedef struct ItemEtcetera {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x14];
} ItemEtcetera; // size = 0x158

extern const ActorInit Item_Etcetera_InitVars;

#endif

#ifndef Z_ITEM_ETCETERA_H
#define Z_ITEM_ETCETERA_H

#include "global.h"

struct ItemEtcetera;

typedef void (*ItemEtceteraActionFunc)(struct ItemEtcetera* this, GlobalContext* globalCtx);

typedef struct ItemEtcetera {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x10];
    /* 0x0154 */ ItemEtceteraActionFunc actionFunc;
} ItemEtcetera; // size = 0x158

extern const ActorInit Item_Etcetera_InitVars;

#endif // Z_ITEM_ETCETERA_H

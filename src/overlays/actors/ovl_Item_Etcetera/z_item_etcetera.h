#ifndef Z_ITEM_ETCETERA_H
#define Z_ITEM_ETCETERA_H

#include "global.h"

struct ItemEtcetera;

#define ITEMETCETERA_GET_FF(thisx) ((thisx)->params & 0xFF)
#define ITEMETCETERA_GET_TREASURE(thisx) (((thisx)->params >> 8) & 0x1F)

typedef void (*ItemEtceteraActionFunc)(struct ItemEtcetera*, GlobalContext*);

typedef struct ItemEtcetera {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ItemEtceteraActionFunc funcSetup;
    /* 0x148 */ s16 itemDrawIndex;
    /* 0x14A */ s16 itemID;
    /* 0x14C */ u8 objIndex;
    /* 0x150 */ ActorFunc drawFunc;
    /* 0x154 */ ItemEtceteraActionFunc actionFunc;
} ItemEtcetera; // size = 0x158

extern const ActorInit Item_Etcetera_InitVars;

#endif // Z_ITEM_ETCETERA_H

#ifndef Z_ITEM_ETCETERA_H
#define Z_ITEM_ETCETERA_H

#include "global.h"

struct ItemEtcetera;

#define ITEMETCETERA_GET_FF(thisx) ((thisx)->params & 0xFF)
#define ITEMETCETERA_GET_TREASURE(thisx) (((thisx)->params >> 8) & 0x1F)

typedef void (*ItemEtceteraActionFunc)(struct ItemEtcetera*, GlobalContext*);

typedef struct ItemEtcetera {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ItemEtceteraActionFunc funcSetup;
    /* 0x148 */ s16 unk_148;
    /* 0x14A */ s16 unk_14A;
    /* 0x14C */ u8 unk_14C;
    /* 0x14D */ ActorFunc drawFunc;
    /* 0x0151 */ ItemEtceteraActionFunc actionFunc;
} ItemEtcetera; // size = 0x155

extern const ActorInit Item_Etcetera_InitVars;

#endif // Z_ITEM_ETCETERA_H

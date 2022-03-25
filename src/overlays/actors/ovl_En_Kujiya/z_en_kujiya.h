#ifndef Z_EN_KUJIYA_H
#define Z_EN_KUJIYA_H

#include "global.h"

struct EnKujiya;

typedef void (*EnKujiyaActionFunc)(struct EnKujiya*, GlobalContext*);

typedef struct EnKujiya {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnKujiyaActionFunc actionFunc;
    /* 0x148 */ s16 unk_148;
    /* 0x14A */ s16 unk_14A;
} EnKujiya; // size = 0x14C

extern const ActorInit En_Kujiya_InitVars;

#endif // Z_EN_KUJIYA_H

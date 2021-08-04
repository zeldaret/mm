#ifndef Z_EN_SCOPECOIN_H
#define Z_EN_SCOPECOIN_H

#include "global.h"

struct EnScopecoin;

typedef void (*EnScopecoinActionFunc)(struct EnScopecoin*, GlobalContext*);

typedef struct EnScopecoin {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnScopecoinActionFunc actionFunc;
    /* 0x148 */ s16 unk148;
    /* 0x14A */ s16 unk14A;
} EnScopecoin; // size = 0x14C

extern const ActorInit En_Scopecoin_InitVars;

#endif // Z_EN_SCOPECOIN_H

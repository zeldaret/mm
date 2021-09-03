#ifndef Z_EN_MK_H
#define Z_EN_MK_H

#include "global.h"

struct EnMk;

typedef void (*EnMkActionFunc)(struct EnMk*, GlobalContext*);

typedef struct EnMk {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x13C];
    /* 0x0280 */ EnMkActionFunc actionFunc;
} EnMk; // size = 0x284

extern const ActorInit En_Mk_InitVars;

#endif // Z_EN_MK_H

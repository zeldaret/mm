#ifndef Z_EN_TITE_H
#define Z_EN_TITE_H

#include "global.h"

struct EnTite;

typedef void (*EnTiteActionFunc)(struct EnTite* this, GlobalContext* globalCtx);

typedef struct EnTite {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x170];
    /* 0x02B4 */ EnTiteActionFunc actionFunc;
    /* 0x02B8 */ char unk_2B8[0x14C];
} EnTite; // size = 0x404

extern const ActorInit En_Tite_InitVars;

#endif // Z_EN_TITE_H

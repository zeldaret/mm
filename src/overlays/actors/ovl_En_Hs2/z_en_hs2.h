#ifndef Z_EN_HS2_H
#define Z_EN_HS2_H

#include "global.h"

struct EnHs2;

typedef void (*EnHs2ActionFunc)(struct EnHs2*, GlobalContext*);

typedef struct EnHs2 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x250];
    /* 0x394 */ EnHs2ActionFunc actionFunc;
} EnHs2; // size = 0x398

extern const ActorInit En_Hs2_InitVars;

#endif // Z_EN_HS2_H

#ifndef Z_EN_BIGSLIME_H
#define Z_EN_BIGSLIME_H

#include "global.h"

struct EnBigslime;

typedef void (*EnBigslimeActionFunc)(struct EnBigslime* this, GlobalContext* globalCtx);

typedef struct EnBigslime {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnBigslimeActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x34A8];
} EnBigslime; // size = 0x3634

extern const ActorInit En_Bigslime_InitVars;

#endif // Z_EN_BIGSLIME_H

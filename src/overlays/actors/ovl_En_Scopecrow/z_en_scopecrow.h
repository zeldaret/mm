#ifndef Z_EN_SCOPECROW_H
#define Z_EN_SCOPECROW_H

#include "global.h"

struct EnScopecrow;

typedef void (*EnScopecrowActionFunc)(struct EnScopecrow* this, GlobalContext* globalCtx);

typedef struct EnScopecrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnScopecrowActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0xDC];
} EnScopecrow; // size = 0x268

extern const ActorInit En_Scopecrow_InitVars;

#endif // Z_EN_SCOPECROW_H

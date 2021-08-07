#ifndef Z_EN_DEKUNUTS_H
#define Z_EN_DEKUNUTS_H

#include "global.h"

struct EnDekunuts;

typedef void (*EnDekunutsActionFunc)(struct EnDekunuts* this, GlobalContext* globalCtx);

typedef struct EnDekunuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnDekunutsActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x13C];
} EnDekunuts; // size = 0x2C8

extern const ActorInit En_Dekunuts_InitVars;

#endif // Z_EN_DEKUNUTS_H

#ifndef Z_EN_PST_H
#define Z_EN_PST_H

#include "global.h"

struct EnPst;

typedef void (*EnPstActionFunc)(struct EnPst* this, GlobalContext* globalCtx);

typedef struct EnPst {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnPstActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x94];
} EnPst; // size = 0x220

extern const ActorInit En_Pst_InitVars;

#endif // Z_EN_PST_H

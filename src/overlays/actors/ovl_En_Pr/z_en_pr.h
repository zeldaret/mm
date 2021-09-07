#ifndef Z_EN_PR_H
#define Z_EN_PR_H

#include "global.h"

struct EnPr;

typedef void (*EnPrActionFunc)(struct EnPr*, GlobalContext*);

typedef struct EnPr {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xBC];
    /* 0x0200 */ EnPrActionFunc actionFunc;
    /* 0x0204 */ char unk_204[0x144];
} EnPr; // size = 0x348

extern const ActorInit En_Pr_InitVars;

#endif // Z_EN_PR_H

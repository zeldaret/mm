#ifndef Z_EN_PR_H
#define Z_EN_PR_H

#include "global.h"

struct EnPr;

typedef void (*EnPrActionFunc)(struct EnPr*, GlobalContext*);

typedef struct EnPr {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xBC];
    /* 0x0200 */ EnPrActionFunc actionFunc;
    /* 0x0204 */ char unk_204[0xC4];
    /* 0x02C8 */ f32 unk_2C8;
    /* 0x02CC */ char unk_2CC[0x7C];
} EnPr; // size = 0x348

extern const ActorInit En_Pr_InitVars;

#endif // Z_EN_PR_H

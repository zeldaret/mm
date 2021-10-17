#ifndef Z_EN_HAKUROCK_H
#define Z_EN_HAKUROCK_H

#include "global.h"

struct EnHakurock;

typedef void (*EnHakurockActionFunc)(struct EnHakurock*, GlobalContext*);

typedef struct EnHakurock {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnHakurockActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x50];
} EnHakurock; // size = 0x198

extern const ActorInit En_Hakurock_InitVars;

#endif // Z_EN_HAKUROCK_H

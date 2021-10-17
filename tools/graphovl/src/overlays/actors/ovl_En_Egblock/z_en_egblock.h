#ifndef Z_EN_EGBLOCK_H
#define Z_EN_EGBLOCK_H

#include "global.h"

struct EnEgblock;

typedef void (*EnEgblockActionFunc)(struct EnEgblock*, GlobalContext*);

typedef struct EnEgblock {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x5C];
    /* 0x01A0 */ EnEgblockActionFunc actionFunc;
    /* 0x01A4 */ char unk_1A4[0xC10];
} EnEgblock; // size = 0xDB4

extern const ActorInit En_Egblock_InitVars;

#endif // Z_EN_EGBLOCK_H

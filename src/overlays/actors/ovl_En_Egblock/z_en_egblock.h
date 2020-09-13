#ifndef Z_EN_EGBLOCK_H
#define Z_EN_EGBLOCK_H

#include <global.h>

struct EnEgblock;

typedef struct EnEgblock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xC70];
} EnEgblock; // size = 0xDB4

extern const ActorInit En_Egblock_InitVars;

#endif // Z_EN_EGBLOCK_H

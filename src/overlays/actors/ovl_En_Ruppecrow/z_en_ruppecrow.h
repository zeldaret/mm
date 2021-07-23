#ifndef Z_EN_RUPPECROW_H
#define Z_EN_RUPPECROW_H

#include "global.h"

struct EnRuppecrow;

typedef struct EnRuppecrow {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1C0];
} EnRuppecrow; // size = 0x304

extern const ActorInit En_Ruppecrow_InitVars;

#endif // Z_EN_RUPPECROW_H

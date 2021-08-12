#ifndef Z_EN_CROW_H
#define Z_EN_CROW_H

#include "global.h"

struct EnCrow;

typedef void (*EnCrowActionFunc)(struct EnCrow*, GlobalContext*);

typedef struct EnCrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnCrowActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x110];
} EnCrow; // size = 0x29C

extern const ActorInit En_Crow_InitVars;

#endif // Z_EN_CROW_H

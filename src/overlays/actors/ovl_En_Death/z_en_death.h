#ifndef Z_EN_DEATH_H
#define Z_EN_DEATH_H

#include "global.h"

struct EnDeath;

typedef void (*EnDeathActionFunc)(struct EnDeath*, GlobalContext*);

typedef struct EnDeath {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnDeathActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x7AC];
} EnDeath; // size = 0x938

extern const ActorInit En_Death_InitVars;

#endif // Z_EN_DEATH_H

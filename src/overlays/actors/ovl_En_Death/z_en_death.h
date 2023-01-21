#ifndef Z_EN_DEATH_H
#define Z_EN_DEATH_H

#include "global.h"

struct EnDeath;

typedef void (*EnDeathActionFunc)(struct EnDeath*, PlayState*);

typedef struct EnDeath {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x44];
    /* 0x188 */ EnDeathActionFunc actionFunc;
    /* 0x18C */ char unk_18C[0x7AC];
} EnDeath; // size = 0x938

#endif // Z_EN_DEATH_H

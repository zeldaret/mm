#ifndef Z_EN_JA_H
#define Z_EN_JA_H

#include "global.h"

struct EnJa;

typedef void (*EnJaActionFunc)(struct EnJa*, GlobalContext*);

typedef struct EnJa {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnJaActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x1EC];
} EnJa; // size = 0x378

extern const ActorInit En_Ja_InitVars;

#endif // Z_EN_JA_H

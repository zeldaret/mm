#ifndef Z_EN_KGY_H
#define Z_EN_KGY_H

#include "global.h"

struct EnKgy;

typedef void (*EnKgyActionFunc)(struct EnKgy*, GlobalContext*);

typedef struct EnKgy {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x1C0];
    /* 0x0304 */ EnKgyActionFunc actionFunc;
} EnKgy; // size = 0x308

extern const ActorInit En_Kgy_InitVars;

#endif // Z_EN_KGY_H

#ifndef Z_EN_BIGPO_H
#define Z_EN_BIGPO_H

#include "global.h"

struct EnBigpo;

typedef void (*EnBigpoActionFunc)(struct EnBigpo*, GlobalContext*);

typedef struct EnBigpo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xBC];
    /* 0x0200 */ EnBigpoActionFunc actionFunc;
    /* 0x0204 */ char unk_204[0x194];
} EnBigpo; // size = 0x398

extern const ActorInit En_Bigpo_InitVars;

#endif // Z_EN_BIGPO_H

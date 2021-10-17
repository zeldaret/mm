#ifndef Z_EN_ELFORG_H
#define Z_EN_ELFORG_H

#include "global.h"

struct EnElforg;

typedef void (*EnElforgActionFunc)(struct EnElforg*, GlobalContext*);

typedef struct EnElforg {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0xE8];
    /* 0x022C */ EnElforgActionFunc actionFunc;
} EnElforg; // size = 0x230

extern const ActorInit En_Elforg_InitVars;

#endif // Z_EN_ELFORG_H

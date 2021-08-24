#ifndef Z_EN_BUTTE_H
#define Z_EN_BUTTE_H

#include "global.h"

struct EnButte;

typedef void (*EnButteActionFunc)(struct EnButte*, GlobalContext*);

typedef struct EnButte {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x104];
    /* 0x0248 */ EnButteActionFunc actionFunc;
    /* 0x024C */ char unk_24C[0x14];
} EnButte; // size = 0x260

extern const ActorInit En_Butte_InitVars;

#endif // Z_EN_BUTTE_H

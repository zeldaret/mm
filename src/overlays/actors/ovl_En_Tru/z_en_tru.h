#ifndef Z_EN_TRU_H
#define Z_EN_TRU_H

#include "global.h"

struct EnTru;

typedef void (*EnTruActionFunc)(struct EnTru*, GlobalContext*);

typedef struct EnTru {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnTruActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x7A8];
} EnTru; // size = 0x934

extern const ActorInit En_Tru_InitVars;

#endif // Z_EN_TRU_H

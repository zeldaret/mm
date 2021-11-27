#ifndef Z_EN_BOMBAL_H
#define Z_EN_BOMBAL_H

#include "global.h"

struct EnBombal;

typedef void (*EnBombalActionFunc)(struct EnBombal*, GlobalContext*);

typedef struct EnBombal {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnBombalActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x28FC];
} EnBombal; // size = 0x2A44

extern const ActorInit En_Bombal_InitVars;

#endif // Z_EN_BOMBAL_H

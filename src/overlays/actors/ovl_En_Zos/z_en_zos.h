#ifndef Z_EN_ZOS_H
#define Z_EN_ZOS_H

#include "global.h"

struct EnZos;

typedef void (*EnZosActionFunc)(struct EnZos*, GlobalContext*);

typedef struct EnZos {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x17C];
    /* 0x02C0 */ EnZosActionFunc actionFunc;
} EnZos; // size = 0x2C4

extern const ActorInit En_Zos_InitVars;

#endif // Z_EN_ZOS_H

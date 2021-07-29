#ifndef Z_EN_DNO_H
#define Z_EN_DNO_H

#include "global.h"

struct EnDno;

typedef void (*EnDnoActionFunc)(struct EnDno* this, GlobalContext* globalCtx);

typedef struct EnDno {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnDnoActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x324];
} EnDno; // size = 0x46C

extern const ActorInit En_Dno_InitVars;

#endif // Z_EN_DNO_H

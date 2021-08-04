#ifndef Z_EN_ELFBUB_H
#define Z_EN_ELFBUB_H

#include "global.h"

struct EnElfbub;

typedef void (*EnElfbubActionFunc)(struct EnElfbub* this, GlobalContext* globalCtx);

typedef struct EnElfbub {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x5C];
    /* 0x01A0 */ EnElfbubActionFunc actionFunc;
} EnElfbub; // size = 0x1A4

extern const ActorInit En_Elfbub_InitVars;

#endif // Z_EN_ELFBUB_H

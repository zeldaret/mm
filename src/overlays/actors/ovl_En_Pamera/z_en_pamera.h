#ifndef Z_EN_PAMERA_H
#define Z_EN_PAMERA_H

#include "global.h"

struct EnPamera;

typedef void (*EnPameraActionFunc)(struct EnPamera* this, GlobalContext* globalCtx);

typedef struct EnPamera {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x90];
    /* 0x01D4 */ EnPameraActionFunc actionFunc;
    /* 0x01D8 */ char unk_1D8[0x150];
} EnPamera; // size = 0x328

extern const ActorInit En_Pamera_InitVars;

#endif // Z_EN_PAMERA_H

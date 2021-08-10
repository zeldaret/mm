#ifndef Z_EN_SC_RUPPE_H
#define Z_EN_SC_RUPPE_H

#include "global.h"

struct EnScRuppe;

typedef void (*EnScRuppeActionFunc)(struct EnScRuppe* this, GlobalContext* globalCtx);

typedef struct EnScRuppe {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x4C];
    /* 0x0190 */ EnScRuppeActionFunc actionFunc;
    /* 0x0194 */ char unk_194[0x4];
} EnScRuppe; // size = 0x198

extern const ActorInit En_Sc_Ruppe_InitVars;

#endif // Z_EN_SC_RUPPE_H

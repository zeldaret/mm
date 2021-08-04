#ifndef Z_EN_KNIGHT_H
#define Z_EN_KNIGHT_H

#include "global.h"

struct EnKnight;

typedef void (*EnKnightActionFunc)(struct EnKnight* this, GlobalContext* globalCtx);

typedef struct EnKnight {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x2DC];
    /* 0x0420 */ EnKnightActionFunc actionFunc;
    /* 0x0424 */ char unk_424[0x2B0];
} EnKnight; // size = 0x6D4

extern const ActorInit En_Knight_InitVars;

#endif // Z_EN_KNIGHT_H

#ifndef Z_EN_RECEPGIRL_H
#define Z_EN_RECEPGIRL_H

#include "global.h"

struct EnRecepgirl;

typedef void (*EnRecepgirlActionFunc)(struct EnRecepgirl* this, GlobalContext* globalCtx);

typedef struct EnRecepgirl {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x164];
    /* 0x02A8 */ EnRecepgirlActionFunc actionFunc;
    /* 0x02AC */ char unk_2AC[0x8];
} EnRecepgirl; // size = 0x2B4

extern const ActorInit En_Recepgirl_InitVars;

#endif // Z_EN_RECEPGIRL_H

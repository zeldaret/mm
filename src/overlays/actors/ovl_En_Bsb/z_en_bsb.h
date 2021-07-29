#ifndef Z_EN_BSB_H
#define Z_EN_BSB_H

#include "global.h"

struct EnBsb;

typedef void (*EnBsbActionFunc)(struct EnBsb* this, GlobalContext* globalCtx);

typedef struct EnBsb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x140];
    /* 0x0284 */ EnBsbActionFunc actionFunc;
    /* 0x0288 */ char unk_288[0xED0];
} EnBsb; // size = 0x1158

extern const ActorInit En_Bsb_InitVars;

#endif // Z_EN_BSB_H

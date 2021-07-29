#ifndef Z_EN_PRZ_H
#define Z_EN_PRZ_H

#include "global.h"

struct EnPrz;

typedef void (*EnPrzActionFunc)(struct EnPrz* this, GlobalContext* globalCtx);

typedef struct EnPrz {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x80];
    /* 0x01C4 */ EnPrzActionFunc actionFunc;
    /* 0x01C8 */ char unk_1C8[0xA8];
} EnPrz; // size = 0x270

extern const ActorInit En_Prz_InitVars;

#endif // Z_EN_PRZ_H

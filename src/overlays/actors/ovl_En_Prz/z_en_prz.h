#ifndef Z_EN_PRZ_H
#define Z_EN_PRZ_H

#include "global.h"

struct EnPrz;

typedef void (*EnPrzActionFunc)(struct EnPrz*, GlobalContext*);

typedef struct EnPrz {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x80];
    /* 0x01C4 */ EnPrzActionFunc actionFunc;
    /* 0x01C8 */ char unk_1C8[0x58];
    /* 0x0220 */ Actor* unk_220;
    /* 0x0224 */ char unk_224[0x4C];
} EnPrz; // size = 0x270

extern const ActorInit En_Prz_InitVars;

#endif // Z_EN_PRZ_H

#ifndef Z_EN_SYATEKI_CROW_H
#define Z_EN_SYATEKI_CROW_H

#include "global.h"

struct EnSyatekiCrow;

typedef void (*EnSyatekiCrowActionFunc)(struct EnSyatekiCrow*, GlobalContext*);

typedef struct EnSyatekiCrow {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x74];
    /* 0x01B8 */ EnSyatekiCrowActionFunc actionFunc;
    /* 0x01BC */ char unk_1BC[0xE0];
} EnSyatekiCrow; // size = 0x29C

extern const ActorInit En_Syateki_Crow_InitVars;

#endif // Z_EN_SYATEKI_CROW_H

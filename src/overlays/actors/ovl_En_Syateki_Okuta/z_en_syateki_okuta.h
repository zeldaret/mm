#ifndef Z_EN_SYATEKI_OKUTA_H
#define Z_EN_SYATEKI_OKUTA_H

#include "global.h"

struct EnSyatekiOkuta;

typedef void (*EnSyatekiOkutaActionFunc)(struct EnSyatekiOkuta*, GlobalContext*);

typedef struct EnSyatekiOkuta {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnSyatekiOkutaActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x120];
} EnSyatekiOkuta; // size = 0x2AC

extern const ActorInit En_Syateki_Okuta_InitVars;

#endif // Z_EN_SYATEKI_OKUTA_H

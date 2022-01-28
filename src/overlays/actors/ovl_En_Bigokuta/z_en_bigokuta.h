#ifndef Z_EN_BIGOKUTA_H
#define Z_EN_BIGOKUTA_H

#include "global.h"

struct EnBigokuta;

typedef void (*EnBigokutaActionFunc)(struct EnBigokuta*, GlobalContext*);

typedef struct EnBigokuta {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x48];
    /* 0x018C */ EnBigokutaActionFunc actionFunc;
    /* 0x0190 */ char unk_190[0x268];
} EnBigokuta; // size = 0x3F8

extern const ActorInit En_Bigokuta_InitVars;

#endif // Z_EN_BIGOKUTA_H

#ifndef Z_EN_MARUTA_H
#define Z_EN_MARUTA_H

#include "global.h"

struct EnMaruta;

typedef void (*EnMarutaActionFunc)(struct EnMaruta*, GlobalContext*);

typedef struct EnMaruta {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnMarutaActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0xDC];
} EnMaruta; // size = 0x224

extern const ActorInit En_Maruta_InitVars;

#endif // Z_EN_MARUTA_H

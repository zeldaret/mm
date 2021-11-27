#ifndef Z_EN_ST_H
#define Z_EN_ST_H

#include "global.h"

struct EnSt;

typedef void (*EnStActionFunc)(struct EnSt*, GlobalContext*);

typedef struct EnSt {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnStActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0x3C4];
} EnSt; // size = 0x550

extern const ActorInit En_St_InitVars;

#endif // Z_EN_ST_H

#ifndef Z_EN_MUTO_H
#define Z_EN_MUTO_H

#include "global.h"

struct EnMuto;

typedef void (*EnMutoActionFunc)(struct EnMuto*, GlobalContext*);

typedef struct EnMuto {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x110];
    /* 0x0254 */ EnMutoActionFunc actionFunc;
    /* 0x0258 */ char unk_258[0x88];
} EnMuto; // size = 0x2E0

extern const ActorInit En_Muto_InitVars;

#endif // Z_EN_MUTO_H

#ifndef Z_EN_ZO_H
#define Z_EN_ZO_H

#include "global.h"

struct EnZo;

typedef void (*EnZoActionFunc)(struct EnZo*, GlobalContext*);

typedef struct EnZo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnZoActionFunc actionFunc;
    /* 0x0148 */ char unk_144[0x2DC];
} EnZo; // size = 0x424

extern const ActorInit En_Zo_InitVars;

#endif // Z_EN_ZO_H

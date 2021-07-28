#ifndef Z_EN_ZO_H
#define Z_EN_ZO_H

#include "global.h"

struct EnZo;

typedef struct EnZo {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x2E0];
} EnZo; // size = 0x424

extern const ActorInit En_Zo_InitVars;

#endif // Z_EN_ZO_H

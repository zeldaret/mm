#ifndef Z_EN_ATTACK_NIW_H
#define Z_EN_ATTACK_NIW_H

#include "global.h"

struct EnAttackNiw;

typedef struct EnAttackNiw {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x19C];
} EnAttackNiw; // size = 0x2E0

extern const ActorInit En_Attack_Niw_InitVars;

#endif // Z_EN_ATTACK_NIW_H

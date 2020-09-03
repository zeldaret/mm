#ifndef _Z_EN_ATTACK_NIW_H_
#define _Z_EN_ATTACK_NIW_H_

#include <global.h>

struct EnAttackNiw;

typedef struct EnAttackNiw {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x19C];
} EnAttackNiw; // size = 0x2E0

extern const ActorInit En_Attack_Niw_InitVars;

#endif

#ifndef Z_EN_ATTACK_NIW_H
#define Z_EN_ATTACK_NIW_H

#include "global.h"

struct EnAttackNiw;

typedef void (*EnAttackNiwActionFunc)(struct EnAttackNiw* this, GlobalContext* globalCtx);

typedef struct EnAttackNiw {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x104];
    /* 0x0248 */ EnAttackNiwActionFunc actionFunc;
    /* 0x024C */ char unk_24C[0x94];
} EnAttackNiw; // size = 0x2E0

extern const ActorInit En_Attack_Niw_InitVars;

#endif // Z_EN_ATTACK_NIW_H

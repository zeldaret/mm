#ifndef Z_EN_OKARINA_EFFECT_H
#define Z_EN_OKARINA_EFFECT_H

#include <global.h>

struct EnOkarinaEffect;

typedef void (*EnOkarinaEffectActionFunc)(struct EnOkarinaEffect*, GlobalContext*);

typedef struct EnOkarinaEffect {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u16 unk144;
    /* 0x146 */ u16 unk146;
    /* 0x148 */ EnOkarinaEffectActionFunc actionFunc;
} EnOkarinaEffect; // size = 0x14C

extern const ActorInit En_Okarina_Effect_InitVars;

#endif // Z_EN_OKARINA_EFFECT_H

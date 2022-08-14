#ifndef Z_EN_TAKARAYA_H
#define Z_EN_TAKARAYA_H

#include "global.h"

struct EnTakaraya;

typedef void (*EnTakarayaActionFunc)(struct EnTakaraya*, PlayState*);

typedef struct EnTakaraya {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x164];
    /* 0x2A8 */ EnTakarayaActionFunc actionFunc;
    /* 0x2AC */ char unk_2AC[0x10];
} EnTakaraya; // size = 0x2BC

extern const ActorInit En_Takaraya_InitVars;

#endif // Z_EN_TAKARAYA_H

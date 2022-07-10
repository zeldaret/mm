#ifndef Z_EFF_LASTDAY_H
#define Z_EFF_LASTDAY_H

#include "global.h"

struct EffLastday;

typedef void (*EffLastdayActionFunc)(struct EffLastday*, PlayState*);

typedef struct EffLastday {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Gfx* unk144;
    /* 0x148 */ AnimatedMaterial* unk148;
    /* 0x14C */ s16 unk14C;
    /* 0x14E */ s16 unk14E;
    /* 0x150 */ s16 unk150;
    /* 0x154 */ EffLastdayActionFunc actionFunc;
} EffLastday; // size = 0x158

extern const ActorInit Eff_Lastday_InitVars;

#endif // Z_EFF_LASTDAY_H

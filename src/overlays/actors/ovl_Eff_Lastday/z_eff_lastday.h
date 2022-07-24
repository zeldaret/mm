#ifndef Z_EFF_LASTDAY_H
#define Z_EFF_LASTDAY_H

#include "global.h"

#define EFFLASTDAY_GET_F(thisx) ((thisx)->params & 0xF)

struct EffLastday;

typedef void (*EffLastdayActionFunc)(struct EffLastday*, PlayState*);

typedef struct EffLastday {
    /* 0x000 */ Actor actor;
    /* 0x144 */ Gfx* dList;
    /* 0x148 */ AnimatedMaterial* matAnim;
    /* 0x14C */ s16 step;
    /* 0x14E */ s16 alpha;
    /* 0x150 */ s16 csActionCmd;
    /* 0x154 */ EffLastdayActionFunc actionFunc;
} EffLastday; // size = 0x158

typedef enum EffLastDayParams {
    /* 0x0 */ EFFLASTDAY_PARAMS_0,
    /* 0x1 */ EFFLASTDAY_PARAMS_1,
    /* 0x2 */ EFFLASTDAY_PARAMS_2,
    /* 0x3 */ EFFLASTDAY_PARAMS_3
} EffLastDayParams;

extern const ActorInit Eff_Lastday_InitVars;

#endif // Z_EFF_LASTDAY_H

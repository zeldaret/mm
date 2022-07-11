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
    /* 0x150 */ s16 actionCmd;
    /* 0x154 */ EffLastdayActionFunc actionFunc;
} EffLastday; // size = 0x158

typedef enum EffLastDayAction {
    /* 0x0 */ ACTION_NONE,
    /* 0x1 */ ACTION_1,
    /* 0x2 */ ACTION_2,
    /* 0x3 */ ACTION_3
} EffLastDayAction;

typedef enum EffLastDayParams {
    /* 0x0 */ PARAMS_0,
    /* 0x1 */ PARAMS_1,
    /* 0x2 */ PARAMS_2,
    /* 0x3 */ PARAMS_3
} EffLastDayParams;

extern const ActorInit Eff_Lastday_InitVars;

#endif // Z_EFF_LASTDAY_H

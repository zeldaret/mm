#ifndef Z_DEMO_TRE_LGT_H
#define Z_DEMO_TRE_LGT_H

#include "global.h"

struct DemoTreLgt;

typedef void (*DemoTreLgtActionFunc)(struct DemoTreLgt* this, GlobalContext* globalCtx);

typedef struct DemoTreLgt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnimeCurve skelCurve;
    /* 0x164 */ s32 action;
    /* 0x168 */ u32 colorAlpha1;
    /* 0x16C */ u32 colorAlpha2;
    /* 0x170 */ u8 status;
    /* 0x174 */ s32 animationType;
} DemoTreLgt; // size = 0x178

typedef enum {
    /* 0x00 */ DEMO_TRE_LGT_ACTION_WAIT, // wait until animation is needed
    /* 0x01 */ DEMO_TRE_LGT_ACTION_ANIMATE
} DemoTreLgtAction;

extern const ActorInit Demo_Tre_Lgt_InitVars;

#endif // Z_DEMO_TRE_LGT_H

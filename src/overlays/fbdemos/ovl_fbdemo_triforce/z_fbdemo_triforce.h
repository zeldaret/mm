#ifndef Z_FBDEMO_TRIFORCE_H
#define Z_FBDEMO_TRIFORCE_H

#include "global.h"

typedef struct {
    /* 0x000 */ Color_RGBA8_u32 color;
    /* 0x004 */ f32 transPos;
    /* 0x008 */ f32 step;
    /* 0x00C */ s32 state;
    /* 0x010 */ s32 fadeDirection;
    /* 0x018 */ Mtx projection;
    /* 0x058 */ s32 frame;
    /* 0x060 */ Mtx modelView[2][3];
} TransitionTriforce; // size = 0x1E0

extern const TransitionInit TransitionTriforce_InitVars;

#endif

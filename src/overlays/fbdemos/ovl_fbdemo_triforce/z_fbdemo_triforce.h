#ifndef Z_FBDEMO_TRIFORCE_H
#define Z_FBDEMO_TRIFORCE_H

#include "global.h"

typedef struct {
    /* 0x0000 */ char unk_0[0x1E0];
} TransitionTriforce; // size = 0x1E0

extern const TransitionInit TransitionTriforce_InitVars;

#endif

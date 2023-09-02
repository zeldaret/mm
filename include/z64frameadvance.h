#ifndef Z64FRAMEADVANCE_H
#define Z64FRAMEADVANCE_H

#include "padmgr.h"

typedef struct FrameAdvanceContext {
    /* 0x0 */ s32 enabled;
    /* 0x4 */ s32 timer;
} FrameAdvanceContext; // size = 0x8


void FrameAdvance_Init(FrameAdvanceContext* frameAdvCtx);
s32 FrameAdvance_Update(FrameAdvanceContext* frameAdvCtx, Input* input);

#endif

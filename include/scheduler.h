#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "PR/ultratypes.h"
#include "PR/sched.h"
#include "ultra64/vi.h"
#include "ultra64/sptask.h"
#include "irqmgr.h"

typedef struct {
    /* 0x00 */ u16*     fb1;
    /* 0x04 */ u16*     swapBuffer;
    /* 0x08 */ OSViMode* viMode;
    /* 0x0C */ u32      features;
    /* 0x10 */ u8       unk_10;
    /* 0x11 */ s8       updateRate;
    /* 0x12 */ s8       updateRate2;
    /* 0x13 */ u8       unk_13;
    /* 0x14 */ f32      xScale;
    /* 0x18 */ f32      yScale;
} CfbInfo; // size = 0x1C

typedef struct {
    /* 0x0000 */ OSMesgQueue interruptQ;
    /* 0x0018 */ OSMesg      intBuf[64];
    /* 0x0118 */ OSMesgQueue cmdQ;
    /* 0x0130 */ OSMesg      cmdMsgBuf[8];
    /* 0x0150 */ OSThread    thread;
    /* 0x0300 */ OSScTask*   audioListHead;
    /* 0x0304 */ OSScTask*   gfxListHead;
    /* 0x0308 */ OSScTask*   audioListTail;
    /* 0x030C */ OSScTask*   gfxListTail;
    /* 0x0310 */ OSScTask*   curRSPTask;
    /* 0x0314 */ OSScTask*   curRDPTask;
    /* 0x0318 */ s32         retraceCount;
    /* 0x0318 */ s32         doAudio;
    /* 0x0320 */ CfbInfo*    curBuf;
    /* 0x0324 */ CfbInfo*    pendingSwapBuf1;
    /* 0x0328 */ CfbInfo*    pendingSwapBuf2;
    /* 0x032C */ char unk_32C[0x3];
    /* 0x032F */ u8 shouldUpdateVi;
    /* 0x0330 */ IrqMgrClient irqClient;
} SchedContext; // size = 0x338

#endif

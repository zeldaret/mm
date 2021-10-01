#ifndef SCHED_H
#define SCHED_H

#include "PR/ultratypes.h"
#include "ultra64/vi.h"
#include "ultra64/sptask.h"
#include "ultra64/message.h"

#define OS_SC_NEEDS_RDP         0x0001
#define OS_SC_NEEDS_RSP         0x0002
#define OS_SC_DRAM_DLIST        0x0004
#define OS_SC_PARALLEL_TASK     0x0010
#define OS_SC_LAST_TASK         0x0020
#define OS_SC_SWAPBUFFER        0x0040

#define OS_SC_RCP_MASK          0x0003
#define OS_SC_TYPE_MASK         0x0007

#define OS_SC_DP                0x0001
#define OS_SC_SP                0x0002
#define OS_SC_YIELD             0x0010
#define OS_SC_YIELDED           0x0020

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

typedef struct OSScTask {
    /* 0x00 */ struct OSScTask* next;
    /* 0x04 */ u32      state;
    /* 0x08 */ u32      flags;
    /* 0x0C */ CfbInfo* framebuffer;
    /* 0x10 */ OSTask   list;
    /* 0x50 */ OSMesgQueue* msgQ;
    /* 0x54 */ OSMesg   msg;
} OSScTask; // size = 0x58

typedef struct IrqMgrClient {
    /* 0x0 */ struct IrqMgrClient* next;
    /* 0x4 */ OSMesgQueue* queue;
} IrqMgrClient; // size = 0x8

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

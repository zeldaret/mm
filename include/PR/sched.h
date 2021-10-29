#ifndef SCHED_H
#define SCHED_H

#include "PR/ultratypes.h"
#include "ultra64/vi.h"
#include "ultra64/sptask.h"

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

typedef struct OSScTask {
    /* 0x00 */ struct OSScTask* next;
    /* 0x04 */ u32      state;
    /* 0x08 */ u32      flags;
    /* 0x0C */ CfbInfo* framebuffer;
    /* 0x10 */ OSTask   list;
    /* 0x50 */ OSMesgQueue* msgQ;
    /* 0x54 */ OSMesg   msg;
} OSScTask; // size = 0x58

typedef struct {
    /* 0x0 */ s16 type;
    /* 0x2 */ u8 misc[30];
} OSScMsg;

#endif

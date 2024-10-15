#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "PR/ultratypes.h"
#include "PR/os_vi.h"
#include "PR/sched.h"
#include "PR/sptask.h"

#include "irqmgr.h"
#include "unk.h"

#define OS_SC_RETRACE_MSG       1
#define OS_SC_DONE_MSG          2
#define OS_SC_NMI_MSG           3 // name is made up, 3 is OS_SC_RDP_DONE_MSG in the original sched.c
#define OS_SC_PRE_NMI_MSG       4

#define TASK_FRAMEBUFFER(task) ((CfbInfo*)(task)->framebuffer)

typedef struct {
    /* 0x00 */ u16* framebuffer; // current framebuffer
    /* 0x04 */ u16* swapBuffer; // framebuffer to swap to
    /* 0x08 */ OSViMode* viMode;
    /* 0x0C */ u32 viFeatures;
    /* 0x10 */ u8 unk_10; // set to 0, never read
    /* 0x11 */ s8 updateRate; // how many VIs should elapse before next swap
    /* 0x12 */ s8 updateTimer; // counts down (in VIs) from updateRate to 0, swaps the framebuffer at 0
    /* 0x14 */ f32 xScale;
    /* 0x18 */ f32 yScale;
} CfbInfo; // size = 0x1C

typedef struct Scheduler {
    /* 0x000 */ OSMesgQueue interruptQueue;
    /* 0x018 */ OSMesg interruptMsgBuf[64];
    /* 0x118 */ OSMesgQueue cmdQueue;
    /* 0x130 */ OSMesg cmdMsgBuf[8];
    /* 0x150 */ OSThread thread;
    /* 0x300 */ OSScTask* audioListHead;
    /* 0x304 */ OSScTask* gfxListHead;
    /* 0x308 */ OSScTask* audioListTail;
    /* 0x30C */ OSScTask* gfxListTail;
    /* 0x310 */ OSScTask* curRSPTask;
    /* 0x314 */ OSScTask* curRDPTask;
    /* 0x318 */ s32 retraceCount;
    /* 0x318 */ s32 doAudio;
    /* 0x320 */ CfbInfo* curBuf; // current framebuffer (taken from buffer 1)
    /* 0x324 */ CfbInfo* pendingSwapBuf1; // buffer 1 (next buffer)
    /* 0x328 */ CfbInfo* pendingSwapBuf2; // buffer 2 (always NULL)
    /* 0x32C */ UNK_TYPE1 unk_32C[0x3];
    /* 0x32F */ u8 isFirstSwap;
    /* 0x330 */ IrqMgrClient irqClient;
} Scheduler; // size = 0x338

void Sched_FlushTaskQueue(void);

void Sched_SendNotifyMsg(Scheduler* sched);
void Sched_SendAudioCancelMsg(Scheduler* sched);
void Sched_SendGfxCancelMsg(Scheduler* sched);

void Sched_Init(Scheduler* sched, void* stack, OSPri pri, u8 viModeType, UNK_TYPE arg4, IrqMgr* irqMgr);

extern Scheduler gScheduler;

#endif

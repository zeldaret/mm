#ifndef IRQMGR_H
#define IRQMGR_H

#include "PR/sched.h"
#include "os.h"
#include "ultra64.h"

#define OS_SC_RETRACE_MSG       1
#define OS_SC_DONE_MSG          2
#define OS_SC_NMI_MSG           3 // name is made up, 3 is OS_SC_RDP_DONE_MSG in the original sched.c
#define OS_SC_PRE_NMI_MSG       4

typedef struct IrqMgrClient {
    /* 0x0 */ struct IrqMgrClient* next;
    /* 0x4 */ OSMesgQueue* queue;
} IrqMgrClient; // size = 0x8

typedef struct {
    /* 0x000 */ OSScMsg verticalRetraceMesg;
    /* 0x020 */ OSScMsg prenmiMsg;
    /* 0x040 */ OSScMsg nmiMsg;
    /* 0x060 */ OSMesgQueue irqQueue;
    /* 0x078 */ OSMesg irqBuffer[8];
    /* 0x098 */ OSThread thread;
    /* 0x248 */ IrqMgrClient* callbacks;
    /* 0x24C */ u8 prenmiStage;
    /* 0x250 */ OSTime lastPrenmiTime;
    /* 0x258 */ OSTimer prenmiTimer;
    /* 0x278 */ OSTime lastFrameTime;
} IrqMgr; // size = 0x280

#endif

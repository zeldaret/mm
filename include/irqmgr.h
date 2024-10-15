#ifndef IRQMGR_H
#define IRQMGR_H

#include "ultra64.h"
#include "PR/sched.h"

typedef enum {
    /* 0 */ IRQ_RESET_STATUS_IDLE,
    /* 1 */ IRQ_RESET_STATUS_PRENMI,
    /* 2 */ IRQ_RESET_STATUS_NMI
} IrqResetStatus;

typedef struct IrqMgrClient {
    /* 0x0 */ struct IrqMgrClient* next;
    /* 0x4 */ OSMesgQueue* queue;
} IrqMgrClient; // size = 0x8

typedef struct IrqMgr {
    /* 0x000 */ OSScMsg retraceMsg;
    /* 0x020 */ OSScMsg prenmiMsg;
    /* 0x040 */ OSScMsg nmiMsg;
    /* 0x060 */ OSMesgQueue queue;
    /* 0x078 */ OSMesg msgBuf[8];
    /* 0x098 */ OSThread thread;
    /* 0x248 */ IrqMgrClient* clients;
    /* 0x24C */ u8 resetStatus;
    /* 0x250 */ OSTime resetTime;
    /* 0x258 */ OSTimer timer;
    /* 0x278 */ OSTime retraceTime;
} IrqMgr; // size = 0x280

extern IrqMgr gIrqMgr;

extern vs32 gIrqMgrResetStatus;
extern volatile OSTime sIrqMgrResetTime;
extern volatile OSTime gIrqMgrRetraceTime;
extern s32 sIrqMgrRetraceCount;

void IrqMgr_AddClient(IrqMgr* irqMgr, IrqMgrClient* client, OSMesgQueue* msgQueue);
void IrqMgr_RemoveClient(IrqMgr* irqMgr, IrqMgrClient* client);
void IrqMgr_Init(IrqMgr* irqMgr, void* stack, OSPri pri, u8 retraceCount);

#endif

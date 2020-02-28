#include <ultra64.h>
#include <global.h>

// TODO move out
#define	OS_CLOCK_RATE		62500000LL
#define	OS_CPU_COUNTER		(OS_CLOCK_RATE*3/4)
#define OS_USEC_TO_CYCLES(n)	(((u64)(n)*(OS_CPU_COUNTER/15625LL))/(1000000LL/15625LL))

vs32 gPrenmiStage = 0;
volatile OSTime sLastPrenmiTime = 0;
vu64 gLastFrameDuration = 0;
s32 sFrameCount = 0;

void IrqMgr_AddCallback(IrqMgr* irqmgr, OSMesgQueueListNode* param_2, OSMesgQueue* param_3) {
    u32 saveMask;

    saveMask = osSetIntMask(1);

    param_2->queue = param_3;
    param_2->next = irqmgr->callbacks;
    irqmgr->callbacks = param_2;

    osSetIntMask(saveMask);

    if (irqmgr->prenmiStage > 0) {
        osSendMesg(param_2->queue, &irqmgr->prenmi1Msg, 0);
    }
    if (irqmgr->prenmiStage > 1) {
        osSendMesg(param_2->queue, &irqmgr->prenmi2Msg, 0);
    }
}

void IrqMgr_RemoveCallback(IrqMgr* irqmgr, OSMesgQueueListNode* remove) {
    OSMesgQueueListNode* iter;
    OSMesgQueueListNode* last;
    u32 saveMask;

    iter = irqmgr->callbacks;
    last = NULL;

    saveMask = osSetIntMask(1);

    while (iter != NULL) {
        if (iter == remove) {
            if (last != NULL) {
                last->next = remove->next;
            } else {
                irqmgr->callbacks = remove->next;
            }
            break;
        }
        last = iter;
        iter = iter->next;
    }

    osSetIntMask(saveMask);
}

void IrqMgr_NotifyAllCallbacks(IrqMgr* irqmgr, OSMesg msg) {
    OSMesgQueueListNode* iter = irqmgr->callbacks;

    while (iter != NULL) {
        osSendMesg(iter->queue, msg, 0);
        iter = iter->next;
    }
}

void IrqMgr_NotifyAllCallbacksWithCapacity(IrqMgr* irqmgr, OSMesg msg) {
    OSMesgQueueListNode* iter = irqmgr->callbacks;

    while (iter != NULL) {
        if (iter->queue->validCount < iter->queue->msgCount) {
            osSendMesg(iter->queue, msg, 0);
        }
        iter = iter->next;
    }
}

void IrqMgr_HandlePrenmi1(IrqMgr* irqmgr) {
    gPrenmiStage = 1;
    irqmgr->prenmiStage = 1;

    sLastPrenmiTime = irqmgr->lastPrenmiTime = osGetTime();

    // Wait .45 seconds then generate a stage 2 prenmi interrupt
    osSetTimer(&irqmgr->prenmiTimer, OS_USEC_TO_CYCLES(450000), 0, &irqmgr->irqQueue, (OSMesg)0x29F);

    IrqMgr_NotifyAllCallbacksWithCapacity(irqmgr, &irqmgr->prenmi1Msg);
}

void IrqMgr_CheckThreadStatusImpl(void) {
    StackCheck_Check(NULL);
}

void IrqMgr_HandlePrenmi2(IrqMgr* irqmgr) {
    gPrenmiStage = 2;
    irqmgr->prenmiStage = 2;

    // Wait .03 seconds then generate a stage 3 prenmi interrupt
    osSetTimer(&irqmgr->prenmiTimer, OS_USEC_TO_CYCLES(30000), 0, &irqmgr->irqQueue, (OSMesg)0x2A0);

    IrqMgr_NotifyAllCallbacks(irqmgr, &irqmgr->prenmi2Msg);
}

void IrqMgr_HandlePrenmi3(IrqMgr* irqmgr) {
    // Wait .52 seconds. After this we will have waited an entire second
    osSetTimer(&irqmgr->prenmiTimer, OS_USEC_TO_CYCLES(520000), 0, &irqmgr->irqQueue, (OSMesg)0x2A1);

    func_8008D710();
}

void IrqMgr_CheckThreadStatus(IrqMgr* irqmgr) {
    IrqMgr_CheckThreadStatusImpl();
}
void IrqMgr_HandleFrame(IrqMgr* irqmgr) {
    if (gLastFrameDuration == 0) {
        if (irqmgr->lastFrameTime == 0) {
            irqmgr->lastFrameTime = osGetTime();
        } else {
            gLastFrameDuration = osGetTime() - irqmgr->lastFrameTime;
        }
    }

    sFrameCount += 1;
    IrqMgr_NotifyAllCallbacks(irqmgr,irqmgr);
}

void IrqMgr_ThreadEntry(IrqMgr* irqmgr) {
    u32 interrupt;
    u32 stop;

    interrupt = 0;
    stop = 0;
    while (stop == 0) {
        if (stop);

        osRecvMesg(&irqmgr->irqQueue, (OSMesg*)&interrupt, 1);
        switch (interrupt) {
        case 0x29A:
            IrqMgr_HandleFrame(irqmgr);
            break;
        case 0x29D:
            IrqMgr_HandlePrenmi1(irqmgr);
            break;
        case 0x29F:
            IrqMgr_HandlePrenmi2(irqmgr);
            break;
        case 0x2A0:
            IrqMgr_HandlePrenmi3(irqmgr);
            break;
        case 0x2A1:
            IrqMgr_CheckThreadStatus(irqmgr);
            break;
        }
    }
}

void IrqMgr_Start(IrqMgr* irqmgr, void* stack, OSPri pri, u8 retraceCount) {
    irqmgr->callbacks = NULL;
    irqmgr->verticalRetraceMesg = 1;
    irqmgr->prenmi1Msg = 4;
    irqmgr->prenmi2Msg = 3;
    irqmgr->prenmiStage = 0;
    irqmgr->lastPrenmiTime = 0;

    osCreateMesgQueue(&irqmgr->irqQueue,(OSMesg *)irqmgr->irqBuffer,8);
    osSetEventMesg(0xE, &irqmgr->irqQueue, (OSMesg)0x29D);
    osViSetEvent(&irqmgr->irqQueue, (OSMesg)0x29A, retraceCount);

    osCreateThread(&irqmgr->thread, 0x13, (osCreateThread_func)IrqMgr_ThreadEntry, irqmgr, stack, pri);
    osStartThread(&irqmgr->thread);
}

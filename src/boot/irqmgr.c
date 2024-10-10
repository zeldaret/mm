/**
 * @file irqMgr.c
 *
 * This file implements a manager for forwarding three key system interrupt events to
 * registered clients.
 * Together with sched.c, these systems implement the libultra video and task scheduling
 * model from the libultra "sched" module, with improved functionality in the handling of
 * Pre-NMI related events.
 *
 * The interrupts the IRQ manager deals with are:
 *  - Vertical Retrace
 *      This event is sent to the IRQ manager by the OS VI manager which only supports
 *      the forwarding of VI events to a single message queue. The IRQ manager will
 *      forward these events to every registered client. Vertical retrace events are
 *      received when the Video Interface has reached the start of the vertical blanking
 *      interval, happening at approximately 60Hz on NTSC and 50Hz on PAL. Many threads
 *      sit idle until a vertical retrace event wakes them up, at which point they will
 *      perform their task and then return to idle to await the next retrace.
 *
 *  - Pre-NMI
 *      This event is sent to the IRQ manager by the OS Interrupt Handler when the reset
 *      button on the N64 control deck is pressed. This event is forwarded to clients to
 *      inform them that a reset will occur in at least 0.5s / 500ms so they may begin any
 *      shutdown procedures.
 *
 *  - NMI
 *      This event is sent at 450ms into the Pre-NMI phase, informing clients that the
 *      mandatory 0.5s of Pre-NMI is almost over and a reset may be imminent. This event
 *      is not to be confused with the hardware NMI interrupt signalled when the CPU is
 *      to fully reset, as by the time that interrupt is received there is no time left
 *      to do anything.
 *
 * @see sched.c
 */
#include "irqmgr.h"

#include "stdbool.h"

#include "macros.h"
#include "scheduler.h"
#include "libu64/stackcheck.h"
#include "z64thread.h"

vs32 gIrqMgrResetStatus = IRQ_RESET_STATUS_IDLE;
volatile OSTime sIrqMgrResetTime = 0;
volatile OSTime gIrqMgrRetraceTime = 0;
s32 sIrqMgrRetraceCount = 0;

// Internal messages
#define IRQ_RETRACE_MSG 666
#define IRQ_PRENMI_MSG 669
#define IRQ_PRENMI450_MSG 671
#define IRQ_PRENMI480_MSG 672
#define IRQ_PRENMI500_MSG 673

/**
 * Registers a client and an associated message queue with the IRQ manager. When an
 * interrupt event is received by the IRQ manager, these clients will be notified of
 * the event.
 *
 * @param irqMgr the IrqMgr instance to register with.
 * @param client client to register.
 * @param msgQueue message queue to send notifications of interrupts to, associated with the client.
 */
void IrqMgr_AddClient(IrqMgr* irqMgr, IrqMgrClient* client, OSMesgQueue* msgQueue) {
    u32 saveMask = osSetIntMask(OS_IM_NONE);

    client->queue = msgQueue;
    client->next = irqMgr->clients;
    irqMgr->clients = client;

    osSetIntMask(saveMask);

    if (irqMgr->resetStatus >= IRQ_RESET_STATUS_PRENMI) {
        osSendMesg(client->queue, (OSMesg)&irqMgr->prenmiMsg, OS_MESG_NOBLOCK);
    }

    if (irqMgr->resetStatus >= IRQ_RESET_STATUS_NMI) {
        osSendMesg(client->queue, (OSMesg)&irqMgr->nmiMsg, OS_MESG_NOBLOCK);
    }
}

void IrqMgr_RemoveClient(IrqMgr* irqMgr, IrqMgrClient* client) {
    IrqMgrClient* iter = irqMgr->clients;
    IrqMgrClient* last = NULL;
    u32 saveMask = osSetIntMask(OS_IM_NONE);

    while (iter != NULL) {
        if (iter == client) {
            if (last != NULL) {
                last->next = client->next;
            } else {
                irqMgr->clients = client->next;
            }
            break;
        }
        last = iter;
        iter = iter->next;
    }

    osSetIntMask(saveMask);
}

/**
 * Send `msg` to every registered client if the message queue is not full. The message is
 * appended to the back of the queue.
 */
void IrqMgr_SendMesgToClients(IrqMgr* irqMgr, OSMesg msg) {
    IrqMgrClient* client = irqMgr->clients;

    while (client != NULL) {
        osSendMesg(client->queue, msg, OS_MESG_NOBLOCK);
        client = client->next;
    }
}

/**
 * Send `msg` to every registered client if the message queue is not full. This appears to be for
 * high-priority messages that should be jammed to the front of the queue, however a bug prevents
 * this from working in this way and the message is appended to the back of the queue as in
 * `IrqMgr_SendMesgToClients`.
 *
 * @see IrqMgr_SendMesgToClients
 */
void IrqMgr_JamMesgToClients(IrqMgr* irqMgr, OSMesg msg) {
    IrqMgrClient* client = irqMgr->clients;

    while (client != NULL) {
        if (!MQ_IS_FULL(client->queue)) {
            //! @bug The function's name suggests this would use osJamMesg rather than osSendMesg, using the
            //! latter makes this function no different than IrqMgr_SendMesgToClients.
            osSendMesg(client->queue, msg, OS_MESG_NOBLOCK);
        }
        client = client->next;
    }
}

/**
 * Runs when the Pre-NMI OS Event is received. This indicates that the console will reset in at least
 * 0.5s / 500ms. Updates the reset status and time before forwarding the Pre-NMI message to registered
 * clients so they may begin shutting down in advance of the reset.
 */
void IrqMgr_HandlePreNMI(IrqMgr* irqMgr) {
    gIrqMgrResetStatus = IRQ_RESET_STATUS_PRENMI;
    irqMgr->resetStatus = IRQ_RESET_STATUS_PRENMI;

    sIrqMgrResetTime = irqMgr->resetTime = osGetTime();

    // Wait .45 seconds then generate a stage 2 prenmi interrupt
    osSetTimer(&irqMgr->timer, OS_USEC_TO_CYCLES(450 * 1000), 0, &irqMgr->queue, (OSMesg)IRQ_PRENMI450_MSG);

    IrqMgr_JamMesgToClients(irqMgr, (OSMesg)&irqMgr->prenmiMsg);
}

void IrqMgr_CheckStacks(void) {
    StackCheck_Check(NULL);
}

void IrqMgr_HandlePRENMI450(IrqMgr* irqMgr) {
    gIrqMgrResetStatus = IRQ_RESET_STATUS_NMI;
    irqMgr->resetStatus = IRQ_RESET_STATUS_NMI;

    // Wait .03 seconds then generate a stage 3 prenmi interrupt
    osSetTimer(&irqMgr->timer, OS_USEC_TO_CYCLES(30 * 1000), 0, &irqMgr->queue, (OSMesg)IRQ_PRENMI480_MSG);

    IrqMgr_SendMesgToClients(irqMgr, (OSMesg)&irqMgr->nmiMsg);
}

void IrqMgr_HandlePRENMI480(IrqMgr* irqMgr) {
    // Wait .52 seconds. After this we will have waited an entire second
    osSetTimer(&irqMgr->timer, OS_USEC_TO_CYCLES(520 * 1000), 0, &irqMgr->queue, (OSMesg)IRQ_PRENMI500_MSG);

    osAfterPreNMI();
}

void IrqMgr_HandlePRENMI500(IrqMgr* irqMgr) {
    IrqMgr_CheckStacks();
}

void IrqMgr_HandleRetrace(IrqMgr* irqMgr) {
    if (gIrqMgrRetraceTime == 0) {
        if (irqMgr->retraceTime == 0) {
            irqMgr->retraceTime = osGetTime();
        } else {
            gIrqMgrRetraceTime = osGetTime() - irqMgr->retraceTime;
        }
    }

    sIrqMgrRetraceCount++;
    IrqMgr_SendMesgToClients(irqMgr, (OSMesg)&irqMgr->retraceMsg);
}

void IrqMgr_ThreadEntry(void* arg) {
    s32 msg = 0;
    IrqMgr* irqMgr = (IrqMgr*)arg;
    s32 exit = false;

    while (!exit) {
        osRecvMesg(&irqMgr->queue, (OSMesg*)&msg, OS_MESG_BLOCK);

        switch (msg) {
            case IRQ_RETRACE_MSG:
                IrqMgr_HandleRetrace(irqMgr);
                break;

            case IRQ_PRENMI_MSG:
                IrqMgr_HandlePreNMI(irqMgr);
                break;

            case IRQ_PRENMI450_MSG:
                IrqMgr_HandlePRENMI450(irqMgr);
                break;

            case IRQ_PRENMI480_MSG:
                IrqMgr_HandlePRENMI480(irqMgr);
                break;

            case IRQ_PRENMI500_MSG:
                IrqMgr_HandlePRENMI500(irqMgr);
                break;

            default:
                break;
        }
    }
}

void IrqMgr_Init(IrqMgr* irqMgr, void* stack, OSPri pri, u8 retraceCount) {
    irqMgr->clients = NULL;
    irqMgr->retraceMsg.type = OS_SC_RETRACE_MSG;
    irqMgr->prenmiMsg.type = OS_SC_PRE_NMI_MSG;
    irqMgr->nmiMsg.type = OS_SC_NMI_MSG;
    irqMgr->resetStatus = IRQ_RESET_STATUS_IDLE;
    irqMgr->resetTime = 0;

    osCreateMesgQueue(&irqMgr->queue, irqMgr->msgBuf, ARRAY_COUNT(irqMgr->msgBuf));
    osSetEventMesg(OS_EVENT_PRENMI, &irqMgr->queue, (OSMesg)IRQ_PRENMI_MSG);
    osViSetEvent(&irqMgr->queue, (OSMesg)IRQ_RETRACE_MSG, retraceCount);

    osCreateThread(&irqMgr->thread, Z_THREAD_ID_IRQMGR, IrqMgr_ThreadEntry, irqMgr, stack, pri);
    osStartThread(&irqMgr->thread);
}

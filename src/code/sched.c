#include "scheduler.h"

#include "libc64/sleep.h"

#include "fault.h"
#include "idle.h"
#include "macros.h"
#include "regs.h"
#include "libu64/stackcheck.h"
#include "viconfig.h"
#include "z64speed_meter.h"
#include "z64thread.h"

FaultClient sSchedFaultClient;

OSTime sRSPGFXStartTime;
OSTime sRSPAudioStartTime;
OSTime sRSPOtherStartTime;
OSTime sRDPStartTime;

u64* gAudioSPDataPtr;
u32 gAudioSPDataSize;

#define RSP_DONE_MSG 667
#define RDP_DONE_MSG 668
#define NOTIFY_MSG 670
#define RDP_AUDIO_CANCEL_MSG 671
#define RSP_GFX_CANCEL_MSG 672

#define OS_SC_DP 0x0001
#define OS_SC_SP 0x0002
#define OS_SC_YIELD 0x0010
#define OS_SC_YIELDED 0x0020

#define OS_SC_XBUS (OS_SC_SP | OS_SC_DP)
#define OS_SC_DRAM (OS_SC_SP | OS_SC_DP | OS_SC_DRAM_DLIST)
#define OS_SC_DP_XBUS (OS_SC_SP)
#define OS_SC_DP_DRAM (OS_SC_SP | OS_SC_DRAM_DLIST)
#define OS_SC_SP_XBUS (OS_SC_DP)
#define OS_SC_SP_DRAM (OS_SC_DP | OS_SC_DRAM_DLIST)

/**
 * Set the current framebuffer to the swapbuffer pointed to by the provided cfb
 */
void Sched_SwapFramebufferImpl(CfbInfo* cfbInfo) {
    if (cfbInfo->swapBuffer != NULL) {
        osViSwapBuffer(cfbInfo->swapBuffer);
        cfbInfo->updateTimer = cfbInfo->updateRate;

        if ((SREG(62) == 0) && (cfbInfo->viMode != NULL)) {
            D_80096B20 = 1;
            osViSetMode(cfbInfo->viMode);
            osViSetSpecialFeatures(cfbInfo->viFeatures);
            osViSetXScale(cfbInfo->xScale);
            osViSetYScale(cfbInfo->yScale);
            cfbInfo->viMode = NULL;
        }
    }
    cfbInfo->unk_10 = 0;
}

void Sched_SwapFramebuffer(Scheduler* sched, CfbInfo* cfbInfo) {
    if (sched->isFirstSwap) {
        sched->isFirstSwap = false;

        if (gIrqMgrResetStatus == IRQ_RESET_STATUS_IDLE) {
            ViConfig_UpdateVi(false);
        }
    }
    Sched_SwapFramebufferImpl(cfbInfo);
}

void Sched_HandlePreNMI(Scheduler* sched) {
}

void Sched_HandleNMI(Scheduler* sched) {
    ViConfig_UpdateVi(true);
}

/**
 * Attempt to stop the RSP, if it is not already halted, by setting the halt bit in the
 * SP status register and waiting. Regardless of the result, the scheduler will send an
 * RSP_DONE_MSG back to itself.
 * If there was no currently running audio task, it will dequeue the currently waiting
 * audio task and notify the sender if the task is associated with a message queue.
 */
void Sched_HandleAudioCancel(Scheduler* sched) {
    s32 i;

    // AUDIO SP Cancel
    osSyncPrintf("AUDIO SP キャンセルします\n");

    if ((sched->curRSPTask != NULL) && (sched->curRSPTask->list.t.type == M_AUDTASK)) {
        if (!(IO_READ(SP_STATUS_REG) & SP_STATUS_HALT)) {
            // Attempts to stop AUDIO SP
            osSyncPrintf("AUDIO SP止めようとします\n");

            IO_WRITE(SP_STATUS_REG, SP_SET_HALT);

            i = 0;
            while (!(IO_READ(SP_STATUS_REG) & SP_STATUS_HALT)) {
                if (i++ > 100) {
                    // AUDIO SP did not stop (10ms timeout)
                    osSyncPrintf("AUDIO SP止まりませんでした(10msタイムアウト)\n");
                    goto send_mesg;
                }
                usleep(100);
            }
            // AUDIO SP stopped (% d * 100us)
            osSyncPrintf("AUDIO SP止まりました(%d * 100us)\n", i);
        } else {
            // AUDIO SP seems to be stopped
            osSyncPrintf("AUDIO SP止まっているようです\n");
        }

    send_mesg:
        osSendMesg(&sched->interruptQueue, (OSMesg)RSP_DONE_MSG, OS_MESG_NOBLOCK);
        return;
    }

    if (sched->audioListHead != NULL) {
        OSScTask* cur = sched->audioListHead;
        OSScTask* next = cur->next;

        sched->audioListHead = next;
        if (next == NULL) {
            sched->audioListTail = NULL;
        }
        if (cur->msgQ != NULL) {
            osSendMesg(cur->msgQ, cur->msg, OS_MESG_BLOCK);
        }
        // Removed AUDIO SP task from pending list
        osSyncPrintf("AUDIO SP タスクを実行待ちリストから削除しました\n");
        return;
    }

    // There are no AUDIO SP tasks to cancel
    osSyncPrintf("キャンセルすべき AUDIO SP タスクがありません\n");
}

/**
 * Attempt to stop the RSP, if it is not already halted, by setting the halt bit in the
 * SP status register and waiting. Regardless of the result, the scheduler will send an
 * RSP_DONE_MSG back to itself and attempt to stop the RDP.
 * If there was no currently running gfx task, it will dequeue the currently waiting gfx
 * task and notify the sender if the task is associated with a message queue.
 * If there is an RDP task, the output buffer will be cleared and the scheduler will send
 * an RDP_DONE_MSG back to itself.
 */
void Sched_HandleGfxCancel(Scheduler* sched) {
    s32 i;

    // GRAPH SP Cancel
    osSyncPrintf("GRAPH SP キャンセルします\n");

    if ((sched->curRSPTask != NULL) && (sched->curRSPTask->list.t.type == M_GFXTASK)) {
        if (!(IO_READ(SP_STATUS_REG) & SP_STATUS_HALT)) {
            // GRAPH SP tries to stop
            osSyncPrintf("GRAPH SP止めようとします\n");

            IO_WRITE(SP_STATUS_REG, SP_SET_HALT);

            i = 0;
            while (!(IO_READ(SP_STATUS_REG) & SP_STATUS_HALT)) {
                if (i++ > 100) {
                    // GRAPH SP did not stop (10ms timeout)
                    osSyncPrintf("GRAPH SP止まりませんでした(10msタイムアウト)\n");
                    goto send_mesg;
                }
                usleep(100);
            }
            // GRAPH SP stopped (%d * 100us)
            osSyncPrintf("GRAPH SP止まりました(%d * 100us)\n", i);
        } else {
            // GRAPH SP seems to be stopped
            osSyncPrintf("GRAPH SP止まっているようです\n");
        }

    send_mesg:
        osSendMesg(&sched->interruptQueue, (OSMesg)RSP_DONE_MSG, OS_MESG_NOBLOCK);
        goto halt_rdp;
    }

    if (sched->gfxListHead != NULL) {
        OSScTask* cur = sched->gfxListHead;
        OSScTask* next = cur->next;

        sched->gfxListHead = next;
        if (next == NULL) {
            sched->gfxListTail = NULL;
        }
        if (cur->msgQ != NULL) {
            osSendMesg(cur->msgQ, cur->msg, OS_MESG_BLOCK);
        }
        goto halt_rdp;
    }

    // There are no GRAPH SP tasks to cancel
    osSyncPrintf("キャンセルすべき GRAPH SP タスクがありません\n");

halt_rdp:
    if (sched->curRDPTask != NULL) {
        OSTask_t* dpTask = &sched->curRDPTask->list.t;

        if (dpTask->type == M_GFXTASK) {
            // Try to stop DP
            osSyncPrintf("DP止めようとします\n");
            bzero(dpTask->output_buff, (uintptr_t)dpTask->output_buff_size - (uintptr_t)dpTask->output_buff);
            osSendMesg(&sched->interruptQueue, (OSMesg)RDP_DONE_MSG, OS_MESG_NOBLOCK);
        }
    }
}

/**
 * Enqueue a task to either the audio task list or the gfx task list
 */
void Sched_QueueTask(Scheduler* sched, OSScTask* task) {
    s32 type = task->list.t.type;

    if (type == M_AUDTASK) {
        if (sched->audioListTail != NULL) {
            sched->audioListTail->next = task;
        } else {
            sched->audioListHead = task;
        }
        sched->audioListTail = task;
    } else {
        if (sched->gfxListTail != NULL) {
            sched->gfxListTail->next = task;
        } else {
            sched->gfxListHead = task;
        }
        sched->gfxListTail = task;
    }
    task->next = NULL;
    task->state = task->flags & OS_SC_RCP_MASK;
}

void Sched_Yield(Scheduler* sched) {
    // Don't yield audio tasks
    if (sched->curRSPTask->list.t.type == M_AUDTASK) {
        // A new audio task has been entered even though the previous audio task has not been completed yet
        osSyncPrintf("まだ前回のオーディオタスクが完了していないのに新たなオーディオタスクがエントリされた\n");
    } else if (!(sched->curRSPTask->state & OS_SC_YIELD)) {
        sched->curRSPTask->state |= OS_SC_YIELD;
        osSpTaskYield();
    }
}

/**
 * Check if the framebuffer the task wants to use is allowed
 */
s32 Sched_TaskFramebuffersValid(Scheduler* sched, OSScTask* task) {
    void* nextFB = osViGetNextFramebuffer();
    void* curFB = osViGetCurrentFramebuffer();

    if ((task == NULL) || (sched->pendingSwapBuf1 != NULL) ||
        ((curFB == TASK_FRAMEBUFFER(task)->framebuffer) && (curFB != nextFB))) {
        return false;
    }

    return true;
}

/**
 * Schedules the next tasks to run on the RSP and RDP
 *
 * @param sc Scheduler
 * @param spTaskOut Next task to run on the RSP
 * @param dpTaskOut Next task to run on the RDP
 * @param state Bits containing whether the RSP and RDP are currently in use
 * @return Bits containing whether the RSP and RDP will be in use after starting the next tasks
 */
s32 Sched_Schedule(Scheduler* sched, OSScTask** spTask, OSScTask** dpTask, s32 state) {
    s32 nextState = state;
    OSScTask* gfxTask = sched->gfxListHead;
    OSScTask* audioTask = sched->audioListHead;

    if ((state & OS_SC_SP) && (sched->audioListHead != NULL)) {
        *spTask = audioTask;
        nextState &= ~OS_SC_SP;
        sched->audioListHead = sched->audioListHead->next;
        if (sched->audioListHead == NULL) {
            sched->audioListTail = NULL;
        }
    } else if (gfxTask != NULL) {
        if ((gfxTask->state & OS_SC_YIELDED) || !(gfxTask->flags & OS_SC_NEEDS_RDP)) {
            if (state & OS_SC_SP) {
                *spTask = gfxTask;
                nextState &= ~OS_SC_SP;
                sched->gfxListHead = sched->gfxListHead->next;
                if (sched->gfxListHead == NULL) {
                    sched->gfxListTail = NULL;
                }
            }
        } else if (state == (OS_SC_SP | OS_SC_DP)) {
            if ((TASK_FRAMEBUFFER(gfxTask) == NULL) || Sched_TaskFramebuffersValid(sched, gfxTask)) {
                *spTask = *dpTask = gfxTask;
                nextState &= ~(OS_SC_SP | OS_SC_DP);
                sched->gfxListHead = sched->gfxListHead->next;
                if (sched->gfxListHead == NULL) {
                    sched->gfxListTail = NULL;
                }
            }
        }
    }
    return nextState;
}

/**
 * Sets the next framebuffer to the framebuffer associated to `task`.
 * If there is no current buffer or it is time to swap, this buffer will be swapped to
 * immediately, otherwise it will be swapped to later in Sched_HandleRetrace.
 *
 * @see Sched_HandleRetrace
 */
void Sched_SetNextFramebufferFromTask(Scheduler* sched, OSScTask* task) {
    sched->pendingSwapBuf1 = TASK_FRAMEBUFFER(task);

    if ((sched->curBuf != NULL) && (sched->curBuf->updateTimer > 0)) {
        return;
    }

    Sched_SwapFramebuffer(sched, sched->pendingSwapBuf1);
}

/**
 * Checks if the task is done, i.e. it is no longer running on either the RSP or RDP.
 * If so, send a message to the task's message queue if there is one, and swap the framebuffer
 * if required.
 */
void Sched_TaskComplete(Scheduler* sched, OSScTask* task) {
    if (!(task->state & (OS_SC_DP | OS_SC_SP))) {
        if (task->msgQ != NULL) {
            osSendMesg(task->msgQ, task->msg, OS_MESG_BLOCK);
        }
        if (task->flags & OS_SC_SWAPBUFFER) {
            Sched_SetNextFramebufferFromTask(sched, task);
        }
    }
}

/**
 * Runs the next tasks. The scheduler doesn't support running RDP tasks without
 * passthrough via the RSP, if there is no RSP task to run then the RDP task will
 * also do nothing.
 */
void Sched_RunTask(Scheduler* sched, OSScTask* spTask, OSScTask* dpTask) {
    OSTime time;

    if (spTask != NULL) {
        if (spTask->list.t.type == M_NULTASK) {
            if (spTask->flags & OS_SC_NEEDS_RSP) {
                spTask->state &= ~OS_SC_SP;
                sched->curRSPTask = NULL;
            }
            if (spTask->flags & OS_SC_NEEDS_RDP) {
                spTask->state &= ~OS_SC_DP;
                sched->curRDPTask = NULL;
            }
            Sched_TaskComplete(sched, spTask);
            return;
        }
        // Write back the data cache to ensure imminent SP DMA does not miss anything
        if ((spTask->list.t.type != M_AUDTASK) && !(spTask->state & OS_SC_YIELDED)) {
            osWritebackDCacheAll();
        }
        spTask->state &= ~(OS_SC_YIELD | OS_SC_YIELDED);
        // Have the RSP download the task and prepare the RSP program counter
        osSpTaskLoad(&spTask->list);

        // Log the start time based on the type of task
        time = osGetTime();
        switch (spTask->list.t.type) {
            case M_AUDTASK:
                sRSPAudioStartTime = time;
                break;

            case M_GFXTASK:
                sRSPGFXStartTime = time;
                break;

            default:
                if (1) {}
                sRSPOtherStartTime = time;
                break;
        }

        if (spTask->list.t.type == M_AUDTASK) {
            // Set global pointers to audio task data for use in audio processing
            gAudioSPDataPtr = spTask->list.t.data_ptr;
            gAudioSPDataSize = spTask->list.t.data_size;
        }

        // Begin task execution
        osSpTaskStartGo(&spTask->list);
        sched->curRSPTask = spTask;
        if (spTask == dpTask && sched->curRDPTask == NULL) {
            sched->curRDPTask = dpTask;
            sRDPStartTime = sRSPGFXStartTime;
        }
    }
}

/**
 * Runs when the scheduler has received a notification, either from another thread or
 * on VI Retrace. Tasks that have been sent to it will be enqueued onto the audio or
 * gfx task queue and one may be ran if the RSP is available.
 */
void Sched_HandleNotify(Scheduler* sched) {
    OSScTask* nextRSP = NULL;
    OSScTask* nextRDP = NULL;
    OSScTask* task = NULL;
    s32 state;

    // Fetch and enqueue waiting tasks
    while (osRecvMesg(&sched->cmdQueue, (OSMesg*)&task, OS_MESG_NOBLOCK) != -1) {
        Sched_QueueTask(sched, task);
    }

    // If there is an audio task pending and an RSP task is running, yield the current task.
    if ((sched->audioListHead != NULL) && (sched->curRSPTask != NULL)) {
        Sched_Yield(sched);
        return;
    }
    // Schedule and run the next task
    state = ((sched->curRSPTask == NULL) << 1) | (sched->curRDPTask == NULL);
    if (Sched_Schedule(sched, &nextRSP, &nextRDP, state) != state) {
        Sched_RunTask(sched, nextRSP, nextRDP);
    }
}

void Sched_HandleRetrace(Scheduler* sched) {
    ViConfig_UpdateBlack();
    sched->retraceCount++;

    if (osViGetCurrentFramebuffer() ==
        (void*)((sched->pendingSwapBuf1 != NULL) ? sched->pendingSwapBuf1->swapBuffer : NULL)) {
        if (sched->curBuf != NULL) {
            sched->curBuf->unk_10 = 0;
        }
        if (sched->pendingSwapBuf1 != NULL) {
            sched->pendingSwapBuf1->unk_10 = 0;
        }
        sched->curBuf = sched->pendingSwapBuf1;
        sched->pendingSwapBuf1 = NULL;
    }

    if (sched->curBuf != NULL) {
        if (sched->curBuf->updateTimer > 0) {
            sched->curBuf->updateTimer--;
        }
        if ((sched->curBuf->updateTimer <= 0) && (sched->pendingSwapBuf1 != NULL)) {
            Sched_SwapFramebuffer(sched, sched->pendingSwapBuf1);
        }
    }

    // Run the notification handler to enqueue any waiting tasks and possibly run one
    Sched_HandleNotify(sched);
}

/**
 * RSP has signalled that the task has either completed or yielded.
 */
void Sched_HandleRSPDone(Scheduler* sched) {
    OSScTask* curRSP;
    OSScTask* nextRSP = NULL;
    OSScTask* nextRDP = NULL;
    s32 state;
    OSTime time;

    if (sched->curRSPTask == NULL) {
        osSyncPrintf("__scHandleRSP:sc->curRSPTask == NULL\n");
        return;
    }

    // Log the time based on the type of task
    time = osGetTime();
    switch (sched->curRSPTask->list.t.type) {
        case M_AUDTASK:
            gRSPAudioTimeAcc += time - sRSPAudioStartTime;
            break;

        case M_GFXTASK:
            gRSPGfxTimeAcc += time - sRSPGFXStartTime;
            break;

        default:
            if (1) {}
            gRSPOtherTimeAcc += time - sRSPOtherStartTime;
            break;
    }

    curRSP = sched->curRSPTask;
    sched->curRSPTask = NULL;

    if (curRSP->list.t.type == M_AUDTASK) {
        // Reset the global audio task data pointers
        gAudioSPDataPtr = NULL;
        gAudioSPDataSize = 0;
    }

    if ((curRSP->state & OS_SC_YIELD) && osSpTaskYielded(&curRSP->list)) {
        // If the task was yielded, re-queue the task
        curRSP->state |= OS_SC_YIELDED;
        curRSP->next = sched->gfxListHead;
        sched->gfxListHead = curRSP;
        if (sched->gfxListTail == NULL) {
            sched->gfxListTail = curRSP;
        }
    } else {
        // Mark task completed
        curRSP->state &= ~OS_SC_SP;
        Sched_TaskComplete(sched, curRSP);
    }

    // Schedule and run next task
    state = ((sched->curRSPTask == NULL) << 1) | (sched->curRDPTask == NULL);
    if (Sched_Schedule(sched, &nextRSP, &nextRDP, state) != state) {
        Sched_RunTask(sched, nextRSP, nextRDP);
    }
}

/**
 * RDP has signalled task done upon reaching a DPFullSync command
 */
void Sched_HandleRDPDone(Scheduler* sched) {
    OSScTask* curRDP;
    OSScTask* nextRSP = NULL;
    OSScTask* nextRDP = NULL;
    s32 state;

    if (sched->curRDPTask == NULL) {
        osSyncPrintf("__scHandleRDP:sc->curRDPTask == NULL\n");
        return;
    }

    // Log run time
    gRDPTimeAcc = osGetTime() - sRDPStartTime;

    // Mark task done
    curRDP = sched->curRDPTask;
    sched->curRDPTask = NULL;
    curRDP->state &= ~OS_SC_DP;

    Sched_TaskComplete(sched, curRDP);

    // Schedule and run next task
    state = ((sched->curRSPTask == NULL) << 1) | (sched->curRDPTask == NULL);
    if (Sched_Schedule(sched, &nextRSP, &nextRDP, state) != state) {
        Sched_RunTask(sched, nextRSP, nextRDP);
    }
}

/**
 * Called by other threads in order to wake the scheduler up immediately to enqueue and
 * possibly run a task that has been sent to the task queue. Otherwise, any pending tasks
 * will be enqueued on next vertical retrace.
 *
 * Original name: osScKickEntryMsg
 */
void Sched_SendNotifyMsg(Scheduler* sched) {
    osSendMesg(&sched->interruptQueue, (OSMesg)NOTIFY_MSG, OS_MESG_BLOCK);
}

/**
 * Sends a message to the scheduler to inform it that it should attempt
 * to stop the last dispatched audio task.
 */
void Sched_SendAudioCancelMsg(Scheduler* sched) {
    osSendMesg(&sched->interruptQueue, (OSMesg)RDP_AUDIO_CANCEL_MSG, OS_MESG_BLOCK);
}

/**
 * Sends a message to the scheduler to inform it that it should attempt
 * to stop the last dispatched gfx task.
 */
void Sched_SendGfxCancelMsg(Scheduler* sched) {
    osSendMesg(&sched->interruptQueue, (OSMesg)RSP_GFX_CANCEL_MSG, OS_MESG_BLOCK);
}

/**
 * Fault Client for the scheduler. Reports information about the state of the scheduler
 * and any current tasks in the crash debugger.
 */
void Sched_FaultClient(void* arg0, void* arg1) {
    Scheduler* sched = (Scheduler*)arg0;
    OSScTask* spTask;
    OSScTask* dpTask;

    FaultDrawer_Printf("sched info\n", sched->gfxListHead, sched->gfxListTail, sched->audioListHead,
                       sched->audioListTail);
    FaultDrawer_Printf("GRAPH %08x %08x\n", sched->gfxListHead, sched->gfxListTail);
    FaultDrawer_Printf("AUDIO %08x %08x\n\n", sched->audioListHead, sched->audioListTail);

    spTask = sched->curRSPTask;
    if (spTask != NULL) {
        FaultDrawer_Printf("RSPTask %08x %08x %02x %02x\n%01x %08x %08x\n", spTask, spTask->next, spTask->state,
                           spTask->flags, spTask->list.t.type, spTask->list.t.data_ptr, spTask->list.t.data_size);
    }

    dpTask = sched->curRDPTask;
    if (dpTask != NULL) {
        FaultDrawer_Printf("RDPTask %08x %08x %02x %02x\n", dpTask, dpTask->next, dpTask->state, dpTask->flags);
    }
}

/**
 * The main loop of the scheduler thread. Processes interrupt messages from
 * the IrqMgr received through its IrqClient and messages sent to it from other
 * threads or the OS.
 */
void Sched_ThreadEntry(void* arg) {
    s32 msg = 0;
    Scheduler* sched = (Scheduler*)arg;

    while (true) {
        osRecvMesg(&sched->interruptQueue, (OSMesg*)&msg, OS_MESG_BLOCK);

        // Check if it's a message from another thread or the OS
        switch (msg) {
            case RDP_AUDIO_CANCEL_MSG:
                Sched_HandleAudioCancel(sched);
                continue;

            case RSP_GFX_CANCEL_MSG:
                Sched_HandleGfxCancel(sched);
                continue;

            case NOTIFY_MSG:
                Sched_HandleNotify(sched);
                continue;

            case RSP_DONE_MSG:
                Sched_HandleRSPDone(sched);
                continue;

            case RDP_DONE_MSG:
                Sched_HandleRDPDone(sched);
                continue;
        }

        // Check if it's a message from the IrqMgr
        switch (((OSScMsg*)msg)->type) {
            case OS_SC_RETRACE_MSG:
                Sched_HandleRetrace(sched);
                continue;

            case OS_SC_PRE_NMI_MSG:
                Sched_HandlePreNMI(sched);
                continue;

            case OS_SC_NMI_MSG:
                Sched_HandleNMI(sched);
                continue;
        }
    }
}

/**
 * Initializes the Scheduler and scheduler thread.
 * Registers an IrqClient for the thread and fault client for the Scheduler.
 * Directs the OS to send SP and DP OS messages to interruptQueue when the RSP or RDP signal task completion.
 */
void Sched_Init(Scheduler* sched, void* stack, OSPri pri, u8 viModeType, UNK_TYPE arg4, IrqMgr* irqMgr) {
    bzero(sched, sizeof(Scheduler));

    sched->isFirstSwap = true;

    osCreateMesgQueue(&sched->interruptQueue, sched->interruptMsgBuf, ARRAY_COUNT(sched->interruptMsgBuf));
    osCreateMesgQueue(&sched->cmdQueue, sched->cmdMsgBuf, ARRAY_COUNT(sched->cmdMsgBuf));
    osSetEventMesg(OS_EVENT_SP, &sched->interruptQueue, (OSMesg)RSP_DONE_MSG);
    osSetEventMesg(OS_EVENT_DP, &sched->interruptQueue, (OSMesg)RDP_DONE_MSG);
    IrqMgr_AddClient(irqMgr, &sched->irqClient, &sched->interruptQueue);
    Fault_AddClient(&sSchedFaultClient, Sched_FaultClient, sched, NULL);
    osCreateThread(&sched->thread, Z_THREAD_ID_SCHED, Sched_ThreadEntry, sched, stack, pri);
    osStartThread(&sched->thread);
}

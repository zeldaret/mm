#include "global.h"

void func_80172C30(AudioMgr* audioMgr) {
    AudioTask* task = audioMgr->rspTask;

    if (audioMgr->rspTask->taskQueue != NULL) {
        osSendMesg(task->taskQueue, NULL, OS_MESG_BLOCK);
    }
}

void AudioMgr_HandleRetrace(AudioMgr* audioMgr) {
    static s32 retryCount = 10;
    AudioTask* rspTask;
    s32 timerMsgVal = 666;
    OSTimer timer;
    s32 msg;

    if (SREG(20) > 0) {
        audioMgr->rspTask = NULL;
    }

    while (audioMgr->cmdQ.validCount != 0) {
        osRecvMesg(&audioMgr->cmdQ, NULL, OS_MESG_NOBLOCK);
    }

    if (audioMgr->rspTask != NULL) {
        audioMgr->audioTask.next = NULL;
        audioMgr->audioTask.flags = OS_SC_NEEDS_RSP;
        audioMgr->audioTask.framebuffer = NULL;

        audioMgr->audioTask.list = audioMgr->rspTask->task;
        audioMgr->audioTask.msgQ = &audioMgr->cmdQ;

        audioMgr->audioTask.msg = NULL;
        osSendMesg(&audioMgr->sched->cmdQ, &audioMgr->audioTask, OS_MESG_BLOCK);
        Sched_SendEntryMsg(audioMgr->sched);
    }

    if (SREG(20) >= 2) {
        rspTask = NULL;
    } else {
        rspTask = func_80192BE0();
    }

    if (audioMgr->rspTask != NULL) {
        while (true) {
            osSetTimer(&timer, OS_USEC_TO_CYCLES(32000), 0, &audioMgr->cmdQ, (OSMesg)timerMsgVal);
            osRecvMesg(&audioMgr->cmdQ, (OSMesg*)&msg, OS_MESG_BLOCK);
            osStopTimer(&timer);
            if (msg == timerMsgVal) {
                osSyncPrintf("AUDIO SP TIMEOUT %08x %08x\n", audioMgr->rspTask, audioMgr->rspTask->task);
                if (retryCount >= 0) {
                    retryCount--;
                    Sched_SendAudioCancelMsg(audioMgr->sched);
                } else {
                    osSyncPrintf("audioMgr.c:もうダメ！死ぬ！\n");
                    osDestroyThread(NULL);
                    break;
                }
            } else {
                break;
            }
        }

        func_80172C30(audioMgr);
    }

    audioMgr->rspTask = rspTask;
}

void AudioMgr_HandlePRENMI(AudioMgr* audioMgr) {
    Audio_PreNMI();
}

void AudioMgr_ThreadEntry(void* arg) {
    AudioMgr* audioMgr = (AudioMgr*)arg;
    IrqMgrClient irqClient;
    s16* msg = NULL;
    s32 exit;

    func_801A4C30();
    AudioLoad_SetDmaHandler(DmaMgr_DmaHandler);
    func_801A4D00();
    osSendMesg(&audioMgr->lockMsgQ, NULL, OS_MESG_BLOCK);
    IrqMgr_AddClient(audioMgr->irqMgr, &irqClient, &audioMgr->interruptMsgQ);

    exit = false;
    while (!exit) {
        osRecvMesg(&audioMgr->interruptMsgQ, (OSMesg*)&msg, OS_MESG_BLOCK);
        switch (*msg) {
            case OS_SC_RETRACE_MSG:
                AudioMgr_HandleRetrace(audioMgr);
                while (audioMgr->interruptMsgQ.validCount != 0) {
                    osRecvMesg(&audioMgr->interruptMsgQ, (OSMesg*)&msg, OS_MESG_BLOCK);
                    switch (*msg) {
                        case OS_SC_RETRACE_MSG:
                            break;
                        case OS_SC_PRE_NMI_MSG:
                            AudioMgr_HandlePRENMI(audioMgr);
                            break;
                        case OS_SC_NMI_MSG:
                            exit = true;
                            break;
                    }
                }
                break;
            case OS_SC_PRE_NMI_MSG:
                AudioMgr_HandlePRENMI(audioMgr);
                break;
            case OS_SC_NMI_MSG:
                exit = true;
                break;
        }
    }

    IrqMgr_RemoveClient(audioMgr->irqMgr, &irqClient);
}

void AudioMgr_Unlock(AudioMgr* audioMgr) {
    osRecvMesg(&audioMgr->lockMsgQ, NULL, OS_MESG_BLOCK);
}

void AudioMgr_Init(AudioMgr* audioMgr, void* stack, OSPri pri, OSId id, SchedContext* sched, IrqMgr* irqMgr) {
    bzero(audioMgr, sizeof(AudioMgr));

    audioMgr->sched = sched;
    audioMgr->irqMgr = irqMgr;
    audioMgr->rspTask = NULL;

    osCreateMesgQueue(&audioMgr->cmdQ, audioMgr->cmdMsgBuf, ARRAY_COUNT(audioMgr->cmdMsgBuf));
    osCreateMesgQueue(&audioMgr->interruptMsgQ, audioMgr->interruptMsgBuf, ARRAY_COUNT(audioMgr->interruptMsgBuf));
    osCreateMesgQueue(&audioMgr->lockMsgQ, audioMgr->lockMsgBuf, ARRAY_COUNT(audioMgr->lockMsgBuf));

    osCreateThread(&audioMgr->thread, id, AudioMgr_ThreadEntry, audioMgr, stack, pri);
    osStartThread(&audioMgr->thread);
}

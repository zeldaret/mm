#include "global.h"
#include "audiomgr.h"

void AudioMgr_NotifyTaskDone(AudioMgr* audioMgr) {
    AudioTask* task = audioMgr->rspTask;

    if (audioMgr->rspTask->taskQueue != NULL) {
        osSendMesg(task->taskQueue, NULL, OS_MESG_BLOCK);
    }
}

void AudioMgr_HandleRetrace(AudioMgr* audioMgr) {
    static s32 sRetryCount = 10;
    AudioTask* rspTask;
    s32 timerMsgVal = 666;
    OSTimer timer;
    s32 msg;

    if (SREG(20) > 0) {
        audioMgr->rspTask = NULL;
    }

    while (!MQ_IS_EMPTY(&audioMgr->cmdQueue)) {
        osRecvMesg(&audioMgr->cmdQueue, NULL, OS_MESG_NOBLOCK);
    }

    if (audioMgr->rspTask != NULL) {
        audioMgr->audioTask.next = NULL;
        audioMgr->audioTask.flags = OS_SC_NEEDS_RSP;
        audioMgr->audioTask.framebuffer = NULL;

        audioMgr->audioTask.list = audioMgr->rspTask->task;
        audioMgr->audioTask.msgQ = &audioMgr->cmdQueue;

        audioMgr->audioTask.msg = NULL;
        osSendMesg(&audioMgr->sched->cmdQ, &audioMgr->audioTask, OS_MESG_BLOCK);
        Sched_SendEntryMsg(audioMgr->sched);
    }

    if (SREG(20) >= 2) {
        rspTask = NULL;
    } else {
        rspTask = AudioThread_Update();
    }

    if (audioMgr->rspTask != NULL) {
        while (true) {
            osSetTimer(&timer, OS_USEC_TO_CYCLES(32000), 0, &audioMgr->cmdQueue, (OSMesg)timerMsgVal);
            osRecvMesg(&audioMgr->cmdQueue, (OSMesg*)&msg, OS_MESG_BLOCK);
            osStopTimer(&timer);
            if (msg == timerMsgVal) {
                osSyncPrintf("AUDIO SP TIMEOUT %08x %08x\n", audioMgr->rspTask, audioMgr->rspTask->task);
                if (sRetryCount >= 0) {
                    sRetryCount--;
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

        AudioMgr_NotifyTaskDone(audioMgr);
    }

    audioMgr->rspTask = rspTask;
}

void AudioMgr_HandlePreNMI(AudioMgr* audioMgr) {
    Audio_PreNMI();
}

void AudioMgr_ThreadEntry(void* arg) {
    AudioMgr* audioMgr = (AudioMgr*)arg;
    IrqMgrClient irqClient;
    s16* msg = NULL;
    s32 exit;

    Audio_Init();
    AudioLoad_SetDmaHandler(DmaMgr_DmaHandler);
    Audio_InitSound();
    osSendMesg(&audioMgr->lockQueue, NULL, OS_MESG_BLOCK);
    IrqMgr_AddClient(audioMgr->irqMgr, &irqClient, &audioMgr->interruptQueue);

    exit = false;
    while (!exit) {
        osRecvMesg(&audioMgr->interruptQueue, (OSMesg*)&msg, OS_MESG_BLOCK);
        switch (*msg) {
            case OS_SC_RETRACE_MSG:
                AudioMgr_HandleRetrace(audioMgr);
                while (!MQ_IS_EMPTY(&audioMgr->interruptQueue)) {
                    osRecvMesg(&audioMgr->interruptQueue, (OSMesg*)&msg, OS_MESG_BLOCK);
                    switch (*msg) {
                        case OS_SC_RETRACE_MSG:
                            break;

                        case OS_SC_PRE_NMI_MSG:
                            AudioMgr_HandlePreNMI(audioMgr);
                            break;

                        case OS_SC_NMI_MSG:
                            exit = true;
                            break;
                    }
                }
                break;

            case OS_SC_PRE_NMI_MSG:
                AudioMgr_HandlePreNMI(audioMgr);
                break;

            case OS_SC_NMI_MSG:
                exit = true;
                break;
        }
    }

    IrqMgr_RemoveClient(audioMgr->irqMgr, &irqClient);
}

void AudioMgr_Unlock(AudioMgr* audioMgr) {
    osRecvMesg(&audioMgr->lockQueue, NULL, OS_MESG_BLOCK);
}

void AudioMgr_Init(AudioMgr* audioMgr, void* stack, OSPri pri, OSId id, SchedContext* sched, IrqMgr* irqMgr) {
    bzero(audioMgr, sizeof(AudioMgr));

    audioMgr->sched = sched;
    audioMgr->irqMgr = irqMgr;
    audioMgr->rspTask = NULL;

    osCreateMesgQueue(&audioMgr->cmdQueue, audioMgr->cmdMsgBuf, ARRAY_COUNT(audioMgr->cmdMsgBuf));
    osCreateMesgQueue(&audioMgr->interruptQueue, audioMgr->interruptMsgBuf, ARRAY_COUNT(audioMgr->interruptMsgBuf));
    osCreateMesgQueue(&audioMgr->lockQueue, audioMgr->lockMsgBuf, ARRAY_COUNT(audioMgr->lockMsgBuf));

    osCreateThread(&audioMgr->thread, id, AudioMgr_ThreadEntry, audioMgr, stack, pri);
    osStartThread(&audioMgr->thread);
}

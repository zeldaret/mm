#include "global.h"
#include "audiomgr.h"

void AudioMgr_NotifyTaskDone(AudioMgr* audioMgr) {
    AudioTask* task = audioMgr->rspTask;

    if (audioMgr->rspTask->taskQueue != NULL) {
        osSendMesg(task->taskQueue, NULL, OS_MESG_BLOCK);
    }
}

void AudioMgr_HandleRetrace(AudioMgr* audioMgr) {
    AudioTask* rspTask;
    s32 timerMsgVal = 666;
    OSTimer timer;
    s32 msg;

    if (R_AUDIOMGR_DEBUG_LEVEL > 0) {
        audioMgr->rspTask = NULL;
    }

#if MM_VERSION >= N64_US
    while (!MQ_IS_EMPTY(&audioMgr->cmdQueue)) {
        osRecvMesg(&audioMgr->cmdQueue, NULL, OS_MESG_NOBLOCK);
    }
#endif

    if (audioMgr->rspTask != NULL) {
        audioMgr->audioTask.next = NULL;
        audioMgr->audioTask.flags = OS_SC_NEEDS_RSP;
        audioMgr->audioTask.framebuffer = NULL;

        audioMgr->audioTask.list = audioMgr->rspTask->task;
        audioMgr->audioTask.msgQ = &audioMgr->cmdQueue;

        audioMgr->audioTask.msg = NULL;
        osSendMesg(&audioMgr->sched->cmdQueue, &audioMgr->audioTask, OS_MESG_BLOCK);
        Sched_SendNotifyMsg(audioMgr->sched);
    }

    if (R_AUDIOMGR_DEBUG_LEVEL >= 2) {
        rspTask = NULL;
    } else {
        rspTask = AudioThread_Update();
    }

    if (audioMgr->rspTask != NULL) {
#if MM_VERSION >= N64_US
        static s32 sRetryCount = 10;
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
                    osSyncPrintf(T("audioMgr.c:もうダメ！死ぬ！\n", "audioMgr.c: I can't go on! I'm dying!\n"));
                    osDestroyThread(NULL);
                    break;
                }
            } else {
                break;
            }
        }
        AudioMgr_NotifyTaskDone(audioMgr);
#else
        // Wait for the audio rsp task scheduled on the previous retrace to complete. This looks like it should wait
        // for the task scheduled on the current retrace, earlier in this function, but since the queue is initially
        // filled in AudioMgr_Init this osRecvMesg call doesn't wait for the task scheduler to post a message for the
        // most recent task as there is already a message waiting.
        osRecvMesg(&audioMgr->cmdQueue, NULL, OS_MESG_BLOCK);
        // Report task done
        //! @bug As the above osRecvMesg is waiting for the previous task to complete rather than the current task,
        //! the task done notification is sent to the task done queue for the current task as soon as the previous task
        //! is completed, without waiting for the current task.
        //! In practice, task done notifications are not used by the audio driver so this is inconsequential.
        AudioMgr_NotifyTaskDone(audioMgr);
#endif
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

    PRINTF(T("オーディオマネージャスレッド実行開始\n", "Start running audio manager thread\n"));

    Audio_Init();
    AudioLoad_SetDmaHandler(DmaMgr_AudioDmaHandler);
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

    PRINTF(T("オーディオマネージャスレッド実行終了\n", "Audio thread manager thread execution end\n"));
}

void AudioMgr_Unlock(AudioMgr* audioMgr) {
    osRecvMesg(&audioMgr->lockQueue, NULL, OS_MESG_BLOCK);
}

void AudioMgr_Init(AudioMgr* audioMgr, void* stack, OSPri pri, OSId id, Scheduler* sched, IrqMgr* irqMgr) {
    bzero(audioMgr, sizeof(AudioMgr));

    audioMgr->sched = sched;
    audioMgr->irqMgr = irqMgr;
    audioMgr->rspTask = NULL;

#if MM_VERSION < N64_US
    R_AUDIOMGR_DEBUG_LEVEL = 1;
#endif

    osCreateMesgQueue(&audioMgr->cmdQueue, audioMgr->cmdMsgBuf, ARRAY_COUNT(audioMgr->cmdMsgBuf));
    osCreateMesgQueue(&audioMgr->interruptQueue, audioMgr->interruptMsgBuf, ARRAY_COUNT(audioMgr->interruptMsgBuf));
    osCreateMesgQueue(&audioMgr->lockQueue, audioMgr->lockMsgBuf, ARRAY_COUNT(audioMgr->lockMsgBuf));

#if MM_VERSION < N64_US
    // Send a message to the task done queue so it is initially full
    osSendMesg(&audioMgr->cmdQueue, NULL, OS_MESG_BLOCK);
#endif

    osCreateThread(&audioMgr->thread, id, AudioMgr_ThreadEntry, audioMgr, stack, pri);
    osStartThread(&audioMgr->thread);
}

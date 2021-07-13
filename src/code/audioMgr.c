#include "global.h"

void func_80172C30(AudioMgr* audioMgr) {
    AudioTask* task = audioMgr->rspTask;

    if (audioMgr->rspTask->taskQueue != NULL) {
        osSendMesg(task->taskQueue, NULL, OS_MESG_BLOCK);
    }
}

void AudioMgr_HandleRetrace(AudioMgr* audioMgr) {
    static s32 D_801D14F0 = 10;
    AudioTask* rspTask;
    s32 timerMsgVal = 666;
    OSTimer timer;
    s32 msg;

    if (SREG(20) > 0) {
        audioMgr->rspTask = NULL;
    }

    if (audioMgr->unk_F4.validCount != 0) {
        do {
            osRecvMesg(&audioMgr->unk_F4, NULL, 0);
        } while (audioMgr->unk_F4.validCount != 0);
    }

    if (audioMgr->rspTask != NULL) {
        audioMgr->audioTask.next = NULL;
        audioMgr->audioTask.flags = 2;
        audioMgr->audioTask.framebuffer = NULL;

        audioMgr->audioTask.list = audioMgr->rspTask->task;
        audioMgr->audioTask.msgQ = &audioMgr->unk_F4;

        audioMgr->audioTask.msg = NULL;
        osSendMesg(&audioMgr->sched->unk118, &audioMgr->audioTask, OS_MESG_BLOCK);
        Sched_SendEntryMsg(audioMgr->sched);
    }

    if (SREG(20) >= 2) {
        rspTask = NULL;
    } else {
        rspTask = func_80192BE0();
    }

    if (audioMgr->rspTask != NULL) {

        while (true) {
            osSetTimer(&timer, 1500000, 0, &audioMgr->unk_F4, (OSMesg)timerMsgVal);
            osRecvMesg(&audioMgr->unk_F4, (OSMesg*)&msg, 1);
            osStopTimer(&timer);
            if (msg == timerMsgVal) {

                Fault_Log("AUDIO SP TIMEOUT %08x %08x\n", audioMgr->rspTask, audioMgr->rspTask->task);

                if (D_801D14F0 >= 0) {
                    D_801D14F0--;
                    func_8017703C(audioMgr->sched);
                } else {
                    Fault_Log("audioMgr.c:もうダメ！死ぬ！\n");
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

void AudioMgr_ThreadEntry(void* arg0) {
    AudioMgr* audioMgr = (AudioMgr*)arg0;
    IrqMgrClient irqClient;
    s16* msg = NULL;
    s32 exit;

    func_801A4C30();
    func_80190B38(DmaMgr_DmaCallback0);
    func_801A4D00();
    osSendMesg(&audioMgr->initDoneCallback, NULL, OS_MESG_BLOCK);
    IrqMgr_AddClient(audioMgr->irqMgr, &irqClient, &audioMgr->irqQueue);

    exit = false;
    while (!exit) {
        osRecvMesg(&audioMgr->irqQueue, (OSMesg*)&msg, OS_MESG_BLOCK);
        switch (*msg) {
            case OS_SC_RETRACE_MSG:
                AudioMgr_HandleRetrace(audioMgr);
                while (audioMgr->irqQueue.validCount != 0) {
                    osRecvMesg(&audioMgr->irqQueue, (OSMesg*)&msg, OS_MESG_BLOCK);
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
    osRecvMesg(&audioMgr->initDoneCallback, NULL, OS_MESG_BLOCK);
}

void AudioMgr_Init(AudioMgr* audioMgr, void* stack, OSPri pri, OSId id, SchedContext* sched, IrqMgr* irqMgr) {
    bzero(audioMgr, sizeof(AudioMgr));

    audioMgr->sched = sched;
    audioMgr->irqMgr = irqMgr;
    audioMgr->rspTask = NULL;

    osCreateMesgQueue(&audioMgr->unk_F4, &audioMgr->unk_10C, 1);
    osCreateMesgQueue(&audioMgr->irqQueue, audioMgr->irqBuffer, 30);
    osCreateMesgQueue(&audioMgr->initDoneCallback, audioMgr->initDoneCallbackMsgBuffer, 1);

    osCreateThread(&audioMgr->thread, id, AudioMgr_ThreadEntry, audioMgr, stack, pri);
    osStartThread(&audioMgr->thread);
}

/**
 * This file has unmigrated bss. It is not practical to migrate it until we have a better way of dealing with bss
 * reordering than just prevent_bss_reordering.h: there is too much of it to control, and it cannot be split into
 * separate files since most of it is at addresses ending in 8.
 */
#include "global.h"

void Main(void* arg) {
    intptr_t fb;
    intptr_t sysHeap;
    s32 exit;
    s16* msg;

    gScreenWidth = SCREEN_WIDTH;
    gScreenHeight = SCREEN_HEIGHT;

    Nmi_Init();
    Fault_Start();
    Check_RegionIsSupported();
    Check_ExpansionPak();

    sysHeap = gSystemHeap;
    fb = 0x80780000;
    startHeapSize = fb - sysHeap;
    SystemArena_Init(sysHeap, startHeapSize);

    GameInfo_Init();

    R_ENABLE_ARENA_DBG = 0;

    osCreateMesgQueue(&sSiIntMsgQ, sSiIntMsgBuf, ARRAY_COUNT(sSiIntMsgBuf));
    osSetEventMesg(OS_EVENT_SI, &sSiIntMsgQ, NULL);

    osCreateMesgQueue(&irqMgrMsgQ, irqMgrMsgBuf, ARRAY_COUNT(irqMgrMsgBuf));

    StackCheck_Init(&schedStackEntry, schedStack, schedStack + sizeof(schedStack), 0, 0x100, "sched");
    Sched_Init(&gSchedContext, schedStack + sizeof(schedStack), Z_PRIORITY_SCHED, D_8009B290, 1, &gIrqMgr);

    CIC6105_AddRomInfoFaultPage();

    IrqMgr_AddClient(&gIrqMgr, &irqClient, &irqMgrMsgQ);

    StackCheck_Init(&audioStackEntry, audioStack, audioStack + sizeof(audioStack), 0, 0x100, "audio");
    AudioMgr_Init(&audioContext, audioStack + sizeof(audioStack), Z_PRIORITY_AUDIOMGR, 0xA, &gSchedContext, &gIrqMgr);

    StackCheck_Init(&padmgrStackEntry, padmgrStack, padmgrStack + sizeof(padmgrStack), 0, 0x100, "padmgr");
    PadMgr_Init(&sSiIntMsgQ, &gIrqMgr, 7, Z_PRIORITY_PADMGR, padmgrStack + sizeof(padmgrStack));

    AudioMgr_Unlock(&audioContext);

    StackCheck_Init(&sGraphStackInfo, sGraphStack, sGraphStack + sizeof(sGraphStack), 0, 0x100, "graph");
    osCreateThread(&sGraphThread, Z_THREAD_ID_GRAPH, Graph_ThreadEntry, arg, sGraphStack + sizeof(sGraphStack),
                   Z_PRIORITY_GRAPH);
    osStartThread(&sGraphThread);

    exit = false;

    while (!exit) {
        msg = NULL;
        osRecvMesg(&irqMgrMsgQ, (OSMesg)&msg, OS_MESG_BLOCK);
        if (msg == NULL) {
            break;
        }

        switch (*msg) {
            case OS_SC_PRE_NMI_MSG:
                Nmi_SetPrenmiStart();
                break;
            case OS_SC_NMI_MSG:
                exit = true;
                break;
        }
    }

    IrqMgr_RemoveClient(&gIrqMgr, &irqClient);
    osDestroyThread(&sGraphThread);
}

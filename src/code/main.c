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

    osCreateMesgQueue(&siEventCallbackQueue, siEventCallbackBuffer, ARRAY_COUNT(siEventCallbackBuffer));
    osSetEventMesg(OS_EVENT_SI, &siEventCallbackQueue, NULL);

    osCreateMesgQueue(&mainIrqmgrCallbackQueue, mainIrqCallbackBuffer, ARRAY_COUNT(mainIrqCallbackBuffer));

    StackCheck_Init(&schedStackEntry, schedStack, schedStack + sizeof(schedStack), 0, 0x100, "sched");
    Sched_Init(&schedContext, schedStack + sizeof(schedStack), Z_PRIORITY_SCHED, D_8009B290, 1, &gIrqMgr);

    CIC6105_AddRomInfoFaultPage();

    IrqMgr_AddClient(&gIrqMgr, &mainIrqmgrCallbackNode, &mainIrqmgrCallbackQueue);

    StackCheck_Init(&audioStackEntry, audioStack, audioStack + sizeof(audioStack), 0, 0x100, "audio");
    AudioMgr_Init(&audioContext, audioStack + sizeof(audioStack), Z_PRIORITY_AUDIOMGR, 0xA, &schedContext, &gIrqMgr);

    StackCheck_Init(&padmgrStackEntry, padmgrStack, padmgrStack + sizeof(padmgrStack), 0, 0x100, "padmgr");
    Padmgr_Start(&siEventCallbackQueue, &gIrqMgr, 7, Z_PRIORITY_PADMGR, padmgrStack + sizeof(padmgrStack));
    
    AudioMgr_Unlock(&audioContext);

    StackCheck_Init(&graphStackEntry, graphStack, graphStack + sizeof(graphStack), 0, 0x100, "graph");
    osCreateThread(&graphOSThread, Z_THREAD_ID_GRAPH, Graph_ThreadEntry, arg, graphStack + sizeof(graphStack),
                   Z_PRIORITY_GRAPH);
    osStartThread(&graphOSThread);

    exit = false;

    while (!exit) {
        msg = NULL;
        osRecvMesg(&mainIrqmgrCallbackQueue, (OSMesg)&msg, OS_MESG_BLOCK);
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

    IrqMgr_RemoveClient(&gIrqMgr, &mainIrqmgrCallbackNode);
    osDestroyThread(&graphOSThread);
}

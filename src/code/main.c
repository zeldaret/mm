/**
 * This file has unmigrated bss. It is not practical to migrate it until we have a better way of dealing with bss
 * reordering than just prevent_bss_reordering.h: there is too much of it to control, and it cannot be split into
 * separate files since most of it is at addresses ending in 8.
 */

#include "global.h"
#include "fault.h"
#include "buffers.h"
#include "stack.h"
#include "stackcheck.h"
#include "system_heap.h"
#include "z64thread.h"

extern OSMesgQueue sSiIntMsgQ;
extern OSMesg sSiIntMsgBuf[1];
extern u32 gSegments[NUM_SEGMENTS];
extern SchedContext gSchedContext;
extern IrqMgrClient irqClient;
extern OSMesgQueue irqMgrMsgQ;
extern OSMesg irqMgrMsgBuf[60];
extern OSThread gGraphThread;
extern STACK(sGraphStack, 0x1800);
extern STACK(sSchedStack, 0x600);
extern STACK(sAudioStack, 0x800);
extern STACK(sPadMgrStack, 0x500);
extern StackEntry sGraphStackInfo;
extern StackEntry sSchedStackInfo;
extern StackEntry sAudioStackInfo;
extern StackEntry sPadMgrStackInfo;
extern AudioMgr sAudioMgr;

void Main(void* arg) {
    intptr_t fb;
    intptr_t sysHeap;
    s32 exit;
    s16* msg;

    gScreenWidth = SCREEN_WIDTH;
    gScreenHeight = SCREEN_HEIGHT;

    Nmi_Init();
    Fault_Init();
    Check_RegionIsSupported();
    Check_ExpansionPak();

    sysHeap = gSystemHeap;
    fb = 0x80780000;
    startHeapSize = fb - sysHeap;
    SystemHeap_Init(sysHeap, startHeapSize);

    Regs_Init();

    R_ENABLE_ARENA_DBG = 0;

    osCreateMesgQueue(&sSiIntMsgQ, sSiIntMsgBuf, ARRAY_COUNT(sSiIntMsgBuf));
    osSetEventMesg(OS_EVENT_SI, &sSiIntMsgQ, NULL);

    osCreateMesgQueue(&irqMgrMsgQ, irqMgrMsgBuf, ARRAY_COUNT(irqMgrMsgBuf));

    StackCheck_Init(&sSchedStackInfo, sSchedStack, STACK_TOP(sSchedStack), 0, 0x100, "sched");
    Sched_Init(&gSchedContext, STACK_TOP(sSchedStack), Z_PRIORITY_SCHED, D_8009B290, 1, &gIrqMgr);

    CIC6105_AddRomInfoFaultPage();

    IrqMgr_AddClient(&gIrqMgr, &irqClient, &irqMgrMsgQ);

    StackCheck_Init(&sAudioStackInfo, sAudioStack, STACK_TOP(sAudioStack), 0, 0x100, "audio");
    AudioMgr_Init(&sAudioMgr, STACK_TOP(sAudioStack), Z_PRIORITY_AUDIOMGR, 0xA, &gSchedContext, &gIrqMgr);

    StackCheck_Init(&sPadMgrStackInfo, sPadMgrStack, STACK_TOP(sPadMgrStack), 0, 0x100, "padmgr");
    PadMgr_Init(&sSiIntMsgQ, &gIrqMgr, 7, Z_PRIORITY_PADMGR, STACK_TOP(sPadMgrStack));

    AudioMgr_Unlock(&sAudioMgr);

    StackCheck_Init(&sGraphStackInfo, sGraphStack, STACK_TOP(sGraphStack), 0, 0x100, "graph");
    osCreateThread(&gGraphThread, Z_THREAD_ID_GRAPH, Graph_ThreadEntry, arg, STACK_TOP(sGraphStack), Z_PRIORITY_GRAPH);
    osStartThread(&gGraphThread);

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
    osDestroyThread(&gGraphThread);
}

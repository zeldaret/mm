#include "global.h"

u8 D_80096B20 = 1;
vu8 gViConfigUseDefault = 1;
u8 gViConfigAdditionalScanLines = 0;
u32 gViConfigFeatures = 0x42;
f32 gViConfigXScale = 1.0f;
f32 gViConfigYScale = 1.0f;

IrqMgr gIrqMgr;
u8 sIrqMgrStack[0x500];
StackEntry sIrqMgrStackInfo;
OSThread gMainThread;
u8 sMainStack[0x900];
StackEntry sMainStackInfo;
OSMesg sPiMgrCmdBuff[50];
OSMesgQueue gPiMgrCmdQ;

void Idle_ClearMemory(void* begin, void* end) {
    if (begin < end) {
        bzero(begin, (uintptr_t)end - (uintptr_t)begin);
    }
}

void Idle_InitFramebuffer(u32* ptr, size_t numBytes, u32 value) {
    s32 temp = sizeof(u32);

    while (numBytes) {
        *ptr++ = value;
        numBytes -= temp;
    }
}

void Idle_InitScreen(void) {
    Idle_InitFramebuffer((u32*)gFramebuffer1, 0x25800, 0x00010001);
    ViConfig_UpdateVi(0);
    osViSwapBuffer(gFramebuffer1);
    osViBlack(false);
}

void Idle_InitMemory(void) {
    u32 pad;
    void* memEnd = OS_PHYSICAL_TO_K0(osMemSize);

    Idle_ClearMemory(0x80000400, gFramebuffer1);
    Idle_ClearMemory(D_80025D00, bootproc);
    Idle_ClearMemory(gGfxSPTaskYieldBuffer, memEnd);
}

void Idle_InitCodeAndMemory(void) {
    DmaRequest dmaReq;
    OSMesgQueue queue;
    OSMesg mesg;
    size_t oldSize;

    osCreateMesgQueue(&queue, &mesg, 1);

    oldSize = sDmaMgrDmaBuffSize;
    sDmaMgrDmaBuffSize = 0;

    DmaMgr_SendRequestImpl(&dmaReq, SEGMENT_START(code), SEGMENT_ROM_START(code),
                           SEGMENT_ROM_END(code) - SEGMENT_ROM_START(code), 0, &queue, 0);
    Idle_InitScreen();
    Idle_InitMemory();
    osRecvMesg(&queue, NULL, OS_MESG_BLOCK);

    sDmaMgrDmaBuffSize = oldSize;

    Idle_ClearMemory(SEGMENT_BSS_START(code), SEGMENT_BSS_END(code));
}

void Main_ThreadEntry(void* arg) {
    StackCheck_Init(&sIrqMgrStackInfo, sIrqMgrStack, sIrqMgrStack + sizeof(sIrqMgrStack), 0, 0x100, "irqmgr");
    IrqMgr_Init(&gIrqMgr, &sIrqMgrStackInfo, Z_PRIORITY_IRQMGR, 1);
    DmaMgr_Start();
    Idle_InitCodeAndMemory();
    Main(arg);
    DmaMgr_Stop();
}

void Idle_InitVideo(void) {
    osCreateViManager(254);

    gViConfigFeatures = 66;
    gViConfigXScale = 1.0;
    gViConfigYScale = 1.0;

    switch (osTvType) {
        case OS_TV_NTSC:
            D_8009B290 = 2;
            gViConfigMode = osViModeNtscLan1;
            break;
        case OS_TV_MPAL:
            D_8009B290 = 30;
            gViConfigMode = osViModeMpalLan1;
            break;
        case OS_TV_PAL:
            D_8009B290 = 44;
            gViConfigMode = osViModeFpalLan1;
            gViConfigYScale = 0.833f;
            break;
    }

    D_80096B20 = 1;
}

void Idle_ThreadEntry(void* arg) {
    Idle_InitVideo();
    osCreatePiManager(150, &gPiMgrCmdQ, sPiMgrCmdBuff, ARRAY_COUNT(sPiMgrCmdBuff));
    StackCheck_Init(&sMainStackInfo, sMainStack, sMainStack + sizeof(sMainStack), 0, 0x400, "main");
    osCreateThread(&gMainThread, Z_THREAD_ID_MAIN, Main_ThreadEntry, arg, sMainStack + sizeof(sMainStack),
                   Z_PRIORITY_MAIN);
    osStartThread(&gMainThread);
    osSetThreadPri(NULL, 0);

    do { } while (true); }

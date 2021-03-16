#include <ultra64.h>
#include <global.h>

u8 D_80096B20 = 1;
vu8 gViConfigUseDefault = 1;
u8 gViConfigAdditionalScanLines = 0;
u32 gViConfigFeatures = 0x42;
f32 gViConfigXScale = 1.0f;
f32 gViConfigYScale = 1.0f;

void Idle_ClearMemory(void* begin, void* end){
    if (begin < end) {
        bzero(begin, (s32)(int)end - (int)begin);
    }
}

#ifdef NON_MATCHING
// This loop shouldn't unroll
void Idle_InitFramebuffer(u32* ptr, u32 numBytes, u32 value) {
    while (numBytes) {
        *ptr++ = value;
        numBytes -= sizeof(u32);
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/boot/idle/Idle_InitFramebuffer.asm")
#endif

void Idle_InitScreen(void) {
    Idle_InitFramebuffer((u32*)&D_80000500, 0x25800, 0x00010001);
    ViConfig_UpdateVi(0);
    osViSwapBuffer(&D_80000500);
    osViBlack(0);
}

void Idle_InitMemory(void) {
    u32 pad;
    void* memEnd = (void*)(0x80000000 + osMemSize);

    Idle_ClearMemory((void*)0x80000400, &D_80000500);
    Idle_ClearMemory(&D_80025D00, (int*)&boot_text_start);
    Idle_ClearMemory(&code_bss_end, memEnd);
}

#ifdef NON_MATCHING
// regalloc around DmaMgr_SendRequestImpl
void Idle_InitCodeAndMemory(void) {
    DmaRequest dmaReq;
    OSMesgQueue queue;
    OSMesg mesg;
    u32 oldSize;

    osCreateMesgQueue(&queue, &mesg, 1);

    oldSize = sDmaMgrDmaBuffSize;
    sDmaMgrDmaBuffSize = 0;

    DmaMgr_SendRequestImpl(&dmaReq, (u32)&code_text_start, (u32)_codeSegmentRomStart, (u32)_codeSegmentRomEnd - (u32)_codeSegmentRomStart, 0, &queue, 0);
    Idle_InitScreen();
    Idle_InitMemory();
    osRecvMesg(&queue, 0, 1);

    sDmaMgrDmaBuffSize = oldSize;

    Idle_ClearMemory(&code_bss_start, &code_bss_end);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/boot/idle/Idle_InitCodeAndMemory.asm")
#endif

void Main_ThreadEntry(void* arg) {
    StackCheck_Init(&sIrqMgrStackInfo, sIrqMgrStack, sIrqMgrStack + sizeof(sIrqMgrStack), 0, 256, "irqmgr");
    IrqMgr_Init(&gIrqMgr, &sIrqMgrStackInfo, 18, 1);
    DmaMgr_Start();
    Idle_InitCodeAndMemory();
    main(arg);
    DmaMgr_Stop();
}

void Idle_InitVideo(void) {
    osCreateViManager(254);

    gViConfigFeatures = 66;
    gViConfigXScale = 1.0;
    gViConfigYScale = 1.0;

    switch (osTvType) {
    case 1:
        D_8009B290 = 2;
        gViConfigMode = osViModeNtscLan1;
        break;
    case 2:
        D_8009B290 = 30;
        gViConfigMode = osViModeMpalLan1;
        break;
    case 0:
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
    StackCheck_Init(&sMainStackInfo, sMainStack, sMainStack + sizeof(sMainStack), 0, 1024, "main");
    osCreateThread(&gMainThread, 3, Main_ThreadEntry, arg, sMainStack + sizeof(sMainStack), 12);
    osStartThread(&gMainThread);
    osSetThreadPri(NULL, 0);

    for(;;);
}

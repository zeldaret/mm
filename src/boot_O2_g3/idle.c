#include <ultra64.h>
#include <global.h>

u8 D_80096B20 = 1;
vu8 D_80096B24 = 1;
u8 D_80096B28 = 0;
u32 viEnabledSpecialFeatures = 0x42;
f32 screenXScale = 1.0f;
f32 screenYScale = 1.0f;

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
GLOBAL_ASM("./asm/non_matchings/idle/Idle_InitFramebuffer.asm")
#endif

void Idle_InitScreen(void) {
    Idle_InitFramebuffer((u32*)&D_80000500, 0x25800, 0x00010001);
    func_800805E0(0);
    osViSwapBuffer(&D_80000500);
    osViRepeatLine(0);
}

void Idle_InitMemory(void) {
    u32 pad;
    void* memEnd = (void*)(0x80000000 + osMemSize);

    Idle_ClearMemory((void*)0x80000400, &D_80000500);
    Idle_ClearMemory(&D_80025D00, (int*)&boot_text_start);
    Idle_ClearMemory(&code_bss_end, memEnd);
}

#ifdef NON_MATCHING
// regalloc around Dmamgr_SendRequest
void Idle_InitCodeAndMemory(void) {
    DmaRequest dmaReq;
    OSMesgQueue queue;
    OSMesg mesg;
    u32 oldSize;

    osCreateMesgQueue(&queue, &mesg, 1);

    oldSize = dmamgrChunkSize;
    dmamgrChunkSize = 0;

    Dmamgr_SendRequest(&dmaReq, (u32)&code_text_start, (u32)&code_vrom_start, (u32)&code_vrom_end - (u32)&code_vrom_start, 0, &queue, 0);
    Idle_InitScreen();
    Idle_InitMemory();
    osRecvMesg(&queue, 0, 1);

    dmamgrChunkSize = oldSize;

    Idle_ClearMemory(&code_bss_start, &code_bss_end);
}
#else
GLOBAL_ASM("./asm/non_matchings/idle/Idle_InitCodeAndMemory.asm")
#endif

void Idle_MainThreadEntry(void* arg) {
    StackCheck_Init(&irqmgrStackEntry, (u32)&irqmgrStack, (u32)&irqmgrStack[1280], 0, 256, "irqmgr");
    IrqMgr_Start(&irqmgrContext, &irqmgrStackEntry, 18, 1);
    Dmamgr_Start();
    Idle_InitCodeAndMemory();
    main(arg);
    Dmamgr_Stop();
}

void func_8008038C(void) {
    osCreateViManager(254);

    viEnabledSpecialFeatures = 66;
    screenXScale = 1.0;
    screenYScale = 1.0;

    switch (osTvType) {
    case 1:
        D_8009B290 = 2;
        D_8009B240 = osViModeNtscLan1;
        break;
    case 2:
        D_8009B290 = 30;
        D_8009B240 = osViModeMpalLan1;
        break;
    case 0:
        D_8009B290 = 44;
        D_8009B240 = D_800980E0;
        screenYScale = 0.833f;
        break;
    }

    D_80096B20 = 1;
}

void Idle_ThreadEntry(void* arg) {
    func_8008038C();
    osCreatePiManager(150, &D_8009B228, D_8009B160, 50);
    StackCheck_Init(&mainStackEntry, (u32)&mainStack, (u32)&mainStack[2304], 0, 1024, "main");
    osCreateThread(&mainOSThread, 3, (osCreateThread_func)Idle_MainThreadEntry, arg, &mainStack[2304], 12);
    osStartThread(&mainOSThread);
    osSetThreadPri(NULL, 0);

    for(;;);
}

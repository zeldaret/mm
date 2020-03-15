#include <ultra64.h>
#include <global.h>

void bootproc(void) {
    StackCheck_Init(&sBootThreadInfo, (u32)sBootThreadStack, (u32)&sBootThreadStack[1024], 0, -1, "boot");
    osMemSize = osGetMemSize();
    func_800818F4();
    osInitialize();
    osUnmapTLBAll();
    gCartHandle = osCartRomInit();
    StackCheck_Init(&sIdleThreadInfo, (u32)sIdleThreadStack, (u32)&sIdleThreadStack[1024], 0, 256, "idle");
    osCreateThread(&sIdleThread, 1, (osCreateThread_func)Idle_ThreadEntry, 0, &sIdleThreadStack[1024], 12);
    osStartThread(&sIdleThread);
}

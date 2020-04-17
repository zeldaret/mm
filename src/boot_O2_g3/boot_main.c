#include <ultra64.h>
#include <global.h>

void bootproc(void) {
    StackCheck_Init(&sBootThreadInfo, sBootThreadStack, &sBootThreadStack[1024], 0, -1, "boot");
    osMemSize = osGetMemSize();
    func_800818F4();
    osInitialize();
    osUnmapTLBAll();
    gCartHandle = osCartRomInit();
    StackCheck_Init(&sIdleThreadInfo, sIdleThreadStack, &sIdleThreadStack[1024], 0, 256, "idle");
    osCreateThread(&sIdleThread, 1, (osCreateThread_func)Idle_ThreadEntry, 0, &sIdleThreadStack[1024], 12);
    osStartThread(&sIdleThread);
}

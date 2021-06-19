#include <ultra64.h>
#include <global.h>

void bootproc(void) {
    StackCheck_Init(&sBootThreadInfo, sBootThreadStack, sBootThreadStack + sizeof(sBootThreadStack), 0, -1, "boot");
    osMemSize = osGetMemSize();
    func_800818F4();
    osInitialize();
    osUnmapTLBAll();
    gCartHandle = osCartRomInit();
    StackCheck_Init(&sIdleThreadInfo, sIdleThreadStack, sIdleThreadStack + sizeof(sIdleThreadStack), 0, 256, "idle");
    osCreateThread(&sIdleThread, Z_THREAD_ID_IDLE, Idle_ThreadEntry, NULL, sIdleThreadStack + sizeof(sIdleThreadStack),
                   Z_PRIORITY_IDLE);
    osStartThread(&sIdleThread);
}

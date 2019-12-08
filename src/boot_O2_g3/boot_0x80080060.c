#include <ultra64.h>
#include <global.h>

UNK_RET start(void) {
    thread_info_init(&bootThreadInfo, bootStack, &bootStack[1024], 0, -1, bootThreadName);
    osMemSize = func_8008D350();
    func_800818F4();
    osInitialize();
    osUnmapTLBAll();
    D_80096B40 = func_80092920();
    thread_info_init(&idleTreadInfo, idleStack, &idleStack[1024], 0, 256, idleThreadName);
    osCreateThread(&idleOSThread, 1, (osCreateThread_func*)Idle_ThreadEntry, 0, &idleTreadInfo, 12);
    osStartThread(&idleOSThread);
}

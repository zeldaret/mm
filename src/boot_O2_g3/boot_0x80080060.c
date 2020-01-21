#include <ultra64.h>
#include <global.h>

void start(void) {
    StackCheck_Init(&bootStackEntry, (u32)bootStack, (u32)&bootStack[1024], 0, -1, "boot");
    osMemSize = osGetMemSize();
    func_800818F4();
    osInitialize();
    osUnmapTLBAll();
    D_80096B40 = osCartRomInit();
    StackCheck_Init(&idleStackEntry, (u32)idleStack, (u32)&idleStack[1024], 0, 256, "idle");
    osCreateThread(&idleOSThread, 1, (osCreateThread_func)Idle_ThreadEntry, 0, &idleStack[1024], 12);
    osStartThread(&idleOSThread);
}

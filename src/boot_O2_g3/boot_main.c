#include "prevent_bss_reordering.h"
#include "global.h"
#include "stack.h"
#include "CIC6105.h"

StackEntry sBootStackInfo;
OSThread sIdleThread;
STACK(sIdleThreadStack, 0x400);
StackEntry sIdleStackInfo;
STACK(sBootThreadStack, 0x400);

void bootproc(void) {
    StackCheck_Init(&sBootStackInfo, sBootThreadStack, STACK_TOP(sBootThreadStack), 0, -1, "boot");
    osMemSize = osGetMemSize();
    func_800818F4();
    osInitialize();
    osUnmapTLBAll();
    gCartHandle = osCartRomInit();
    StackCheck_Init(&sIdleStackInfo, sIdleThreadStack, STACK_TOP(sIdleThreadStack), 0, 0x100, "idle");
    osCreateThread(&sIdleThread, Z_THREAD_ID_IDLE, Idle_ThreadEntry, NULL, STACK_TOP(sIdleThreadStack),
                   Z_PRIORITY_IDLE);
    osStartThread(&sIdleThread);
}

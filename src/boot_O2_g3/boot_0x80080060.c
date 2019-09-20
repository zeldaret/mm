#include <ultra64.h>
#include <global.h>

UNK_RET start(void) {
    thread_info_init(&D_80099500, &D_80099AF0, &D_80099EF0, 0, -1, &D_80098190);
    osMemSize = func_8008D350();
    func_800818F4();
    osInitialize();
    osUnmapTLBAll();
    D_80096B40 = func_80092920();
    thread_info_init(&D_80099AD0, &D_800996D0, &D_80099AD0_, 0, 256, &D_80098198);
    osCreateThread(&D_80099520, 1, (void(*)(void*))Idle_ThreadEntry, 0, &D_80099AD0, 12);
    osStartThread(&D_80099520);
}

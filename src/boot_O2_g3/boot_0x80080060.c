#include <ultra64.h>
#include <global.h>

UNK_RET func_80080060(void) {
    func_80085320(&D_80099500, &D_80099AF0, &D_80099EF0, 0, -1, &D_80098190);
    osMemSize = func_8008D350();
    func_800818F4();
    osInitialize();
    osUnmapTLBAll();
    D_80096B40 = func_80092920();
    func_80085320(&D_80099AD0, &D_800996D0, &D_80099AD0_, 0, 256, &D_80098198);
    osCreateThread(&D_80099520, 1, (void(*)(void*))func_80080514, 0, &D_80099AD0, 12);
    osStartThread(&D_80099520);
}

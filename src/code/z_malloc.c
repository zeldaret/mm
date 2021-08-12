#include "global.h"

void* ZeldaArena_Malloc(size_t size) {
    void* ptr = __osMalloc(&sZeldaArena, size);

    return ptr;
}

void* ZeldaArena_MallocR(size_t size) {
    void* ptr = __osMallocR(&sZeldaArena, size);

    return ptr;
}

void* ZeldaArena_Realloc(void* ptr, size_t newSize) {
    ptr = __osRealloc(&sZeldaArena, ptr, newSize);
    return ptr;
}

void ZeldaArena_Free(void* ptr) {
    __osFree(&sZeldaArena, ptr);
}

void* ZeldaArena_Calloc(u32 num, size_t size) {
    void* ret;
    u32 n = num * size;

    ret = __osMalloc(&sZeldaArena, n);
    if (ret != NULL) {
        bzero(ret, n);
    }

    return ret;
}

void ZeldaArena_GetSizes(u32* outMaxFree, u32* outFree, u32* outAlloc) {
    __osAnalyzeArena(&sZeldaArena, outMaxFree, outFree, outAlloc);
}

void ZeldaArena_Check() {
    __osCheckArena(&sZeldaArena);
}

void ZeldaArena_Init(void* start, size_t size) {
    __osMallocInit(&sZeldaArena, start, size);
}

void ZeldaArena_Cleanup() {
    __osMallocCleanup(&sZeldaArena);
}

u8 ZeldaArena_IsInitialized() {
    return __osMallocIsInitalized(&sZeldaArena);
}

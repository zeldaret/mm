#include "global.h"

Arena gSystemArena;

void* SystemArena_Alloc(u32 size) {
    return __osMalloc(&gSystemArena, size);
}

void* SystemArena_AllocR(u32 size) {
    return __osMallocR(&gSystemArena, size);
}

void* SystemArena_Realloc(void* oldPtr, u32 newSize) {
    return __osRealloc(&gSystemArena, oldPtr, newSize);
}

void SystemArena_Free(void* ptr) {
    __osFree(&gSystemArena, ptr);
}

void* SystemArena_Calloc(u32 elements, u32 size) {
    void* ptr;
    u32 totalSize = elements * size;

    ptr = __osMalloc(&gSystemArena, totalSize);
    if (ptr != NULL) {
        bzero(ptr, totalSize);
    }
    return ptr;
}

void SystemArena_AnalyzeArena(u32* maxFreeBlock, u32* bytesFree, u32* bytesAllocated) {
    __osAnalyzeArena(&gSystemArena, maxFreeBlock, bytesFree, bytesAllocated);
}

u32 SystemArena_CheckArena(void) {
    return __osCheckArena(&gSystemArena);
}

void SystemArena_InitArena(void* start, u32 size) {
    __osMallocInit(&gSystemArena, start, size);
}

void SystemArena_Cleanup(void) {
    __osMallocCleanup(&gSystemArena);
}

u8 SystemArena_IsInitialized(void) {
    return __osMallocIsInitalized(&gSystemArena);
}

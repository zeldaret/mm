#include "libc64/malloc.h"

Arena malloc_arena;

void* malloc(size_t size) {
    return __osMalloc(&malloc_arena, size);
}

void* malloc_r(size_t size) {
    return __osMallocR(&malloc_arena, size);
}

void* realloc(void* oldPtr, size_t newSize) {
    return __osRealloc(&malloc_arena, oldPtr, newSize);
}

void free(void* ptr) {
    __osFree(&malloc_arena, ptr);
}

void* calloc(size_t num, size_t size) {
    void* ptr;
    size_t totalSize = num * size;

    ptr = __osMalloc(&malloc_arena, totalSize);
    if (ptr != NULL) {
        bzero(ptr, totalSize);
    }
    return ptr;
}

void GetFreeArena(size_t* maxFreeBlock, size_t* bytesFree, size_t* bytesAllocated) {
    __osGetSizes(&malloc_arena, maxFreeBlock, bytesFree, bytesAllocated);
}

s32 CheckArena(void) {
    return __osCheckArena(&malloc_arena);
}

void MallocInit(void* start, size_t size) {
    __osMallocInit(&malloc_arena, start, size);
}

void MallocCleanup(void) {
    __osMallocCleanup(&malloc_arena);
}

s32 MallocIsInitialized(void) {
    return __osMallocIsInitalized(&malloc_arena);
}

#ifndef LIBC64_MALLOC_H
#define LIBC64_MALLOC_H

#include "ultra64.h"
#include "libc64/os_malloc.h"

void* malloc(size_t size);
void* malloc_r(size_t size);
void* realloc(void* oldPtr, size_t newSize);
void free(void* ptr);
void* calloc(size_t num, size_t size);
void GetFreeArena(size_t* maxFreeBlock, size_t* bytesFree, size_t* bytesAllocated);
s32 CheckArena(void);
void MallocInit(void* start, size_t size);
void MallocCleanup(void);
s32 MallocIsInitialized(void);

extern Arena malloc_arena;

#endif

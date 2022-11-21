#ifndef SYSTEM_HEAP
#define SYSTEM_HEAP

#include "libc/stddef.h"
#include "PR/ultratypes.h"

void SystemHeap_Init(void* start, size_t size);

#endif

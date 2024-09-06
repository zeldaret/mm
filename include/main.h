#ifndef MAIN_H
#define MAIN_H

#include "ultra64.h"

#include "stdint.h"

extern s32 gScreenWidth;
extern s32 gScreenHeight;
extern size_t gSystemHeapSize;

extern uintptr_t gSegments[NUM_SEGMENTS];
extern OSThread gGraphThread;

void Main(void* arg);

#define SEGMENTED_TO_K0(addr) (void*)((gSegments[SEGMENT_NUMBER(addr)] + K0BASE) + SEGMENT_OFFSET(addr))

#endif

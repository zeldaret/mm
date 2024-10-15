#ifndef SEGMENTED_ADDRESS_H
#define SEGMENTED_ADDRESS_H

#include "ultra64.h"

#include "stdint.h"

extern uintptr_t gSegments[NUM_SEGMENTS];

#define SEGMENTED_TO_K0(addr) (void*)((gSegments[SEGMENT_NUMBER(addr)] + K0BASE) + SEGMENT_OFFSET(addr))

#endif

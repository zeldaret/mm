#ifndef ULTRA64_VIINT_H
#define ULTRA64_VIINT_H

#include "ultratypes.h"


typedef struct {
    /* 0x0 */ f32 factor;
    /* 0x4 */ u16 offset;
    /* 0x8 */ u32 scale;
} __OSViScale; // size = 0x0C

typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 retraceCount;
    /* 0x04 */ void* buffer;
    /* 0x08 */ OSViMode* modep;
    /* 0x0C */ u32 features;
    /* 0x10 */ OSMesgQueue* mq;
    /* 0x14 */ OSMesg* msg;
    /* 0x18 */ __OSViScale x;
    /* 0x24 */ __OSViScale y;
} __OSViContext; // size = 0x30

void __osViSwapContext(void);
__OSViContext* __osViGetCurrentContext(void);
void __osViInit(void);


#endif

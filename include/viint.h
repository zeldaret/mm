#ifndef _VIINT_H_
#define _VIINT_H_

// TODO should be in libultra/io

#include <PR/ultratypes.h>
#include <os.h>

typedef struct {
    /* 0 */ f32 factor;
    /* 4 */ u16 offset;
    /* 8 */ u32 scale;
} __OSViScale;


typedef struct {
    /* 0 */ u16 state;
    /* 2 */ u16 retraceCount;
    /* 4 */ void* framep;
    /* 8 */ OSViMode* modep;
    /* 12 */ u32 control;
    /* 16 */ OSMesgQueue* msgq;
    /* 20 */ OSMesg msg;
    /* 24 */ __OSViScale x;
    /* 36 */ __OSViScale y;
} __OSViContext;

#endif

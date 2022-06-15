#ifndef _VIINT_H_
#define _VIINT_H_

// TODO should be in libultra/io

#include "PR/ultratypes.h"
#include "os.h"

// typedef struct {
//     /* 0x0 */ f32 factor;
//     /* 0x4 */ u16 offset;
//     /* 0x8 */ u32 scale;
// } __OSViScale;


typedef struct {
    /* 0x0 */ u16 state;
    /* 0x2 */ u16 retraceCount;
    /* 0x4 */ void* buffer;
    /* 0x8 */ OSViMode* modep;
    /* 0xC */ u32 control;
    /* 0x10 */ OSMesgQueue* msgq;
    /* 0x14 */ OSMesg msg;
    /* 0x18 */ __OSViScale x;
    /* 0x24 */ __OSViScale y;
} __OSViContext; // size = 0x30

#endif

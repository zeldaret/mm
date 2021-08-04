#ifndef _COLOR_H_
#define _COLOR_H_

#include "PR/ultratypes.h"

typedef struct {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
} Color_RGB8; // size = 0x3

typedef struct {
    /* 0x0 */ u8 r;
    /* 0x1 */ u8 g;
    /* 0x2 */ u8 b;
    /* 0x3 */ u8 a;
} Color_RGBA8; // size = 0x4

// only use when necessary for alignment purposes
typedef union {
    struct {
        u8 r, g, b, a;
    };
    u32 rgba;
} Color_RGBA8_u32;

typedef struct {
    f32 r, g, b, a;
} Color_RGBAf;

typedef union {
    struct {
        u16 r : 5;
        u16 g : 5;
        u16 b : 5;
        u16 a : 1;
    };
    u16 rgba;
} Color_RGB5A1;

#endif

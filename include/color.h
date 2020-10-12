#ifndef _COLOR_H_
#define _COLOR_H_

#include <PR/ultratypes.h>

typedef struct {
    /* 0x0 */ u8 red;
    /* 0x1 */ u8 green;
    /* 0x2 */ u8 blue;
    /* 0x3 */ u8 alpha;
} ColorRGBA8; // size = 0x4

typedef struct {
    /* 0x0 */ u8 red;
    /* 0x1 */ u8 green;
    /* 0x2 */ u8 blue;
} RGB; // size = 0x3

typedef struct {
    /* 0x0 */ u8 red;
    /* 0x1 */ u8 green;
    /* 0x2 */ u8 blue;
    /* 0x3 */ u8 alpha;
} RGBA8; // size = 0x4

typedef struct {
    u8 r, g, b, a;
} Color_RGBA8_n;

#endif

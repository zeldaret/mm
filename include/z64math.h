#ifndef _Z64MATH_H_
#define _Z64MATH_H_

#include <ultra64.h>

#define SHT_MAX 32767.0f
#define M_PI 3.14159265358979323846f

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} Vec3f; // size = 0xC

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
} Vec3s; // size = 0x6

#endif

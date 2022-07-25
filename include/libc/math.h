#ifndef MATH_H
#define MATH_H

#include "PR/ultratypes.h"

#define M_PI 3.14159265358979323846f
#define M_SQRT2 1.41421356237309504880f
#define M_SQRT1_2 0.70710678118654752440f	/* 1/sqrt(2) */
#define FLT_MAX 340282346638528859811704183484516925440.0f
#define SHT_MAX 32767.0f
#define SHT_MINV (1.0f / SHT_MAX)

typedef union {
    f64 d;
    struct {
        u32 hi;
        u32 lo;
    } word;
} du;

typedef union {
    u32 i;
    f32 f;
} fu;

extern f32 __libm_qnan_f;

float fabsf(float f);
#pragma intrinsic(fabsf)
float sqrtf(float f);
#pragma intrinsic(sqrtf)
double sqrt(double d);
#pragma intrinsic(sqrt)

#endif

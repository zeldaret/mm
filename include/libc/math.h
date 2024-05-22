#ifndef LIBC_MATH_H
#define LIBC_MATH_H

#define M_PI 3.14159265358979323846
#define M_PIf 3.14159265358979323846f
#define M_SQRT2f 1.41421356237309504880f
#define M_SQRT1_2f 0.70710678118654752440f /* 1/sqrt(2) */

#define FLT_MAX 3.40282347e+38f
#define SHRT_MAX 32767.0f

float fabsf(float f);
#pragma intrinsic(fabsf)
#ifdef __GNUC__
#define fabsf(f) __builtin_fabsf((float)(f))
#endif

double sqrt(double d);
#pragma intrinsic(sqrt)

float fmodf(float dividend, float divisor);

#endif

#ifndef LIBC_MATH_H
#define LIBC_MATH_H

#define M_PI 3.14159265358979323846f
#define M_SQRT2 1.41421356237309504880f
#define M_SQRT1_2 0.70710678118654752440f	/* 1/sqrt(2) */
#define FLT_MAX 340282346638528859811704183484516925440.0f
#define SHT_MAX 32767.0f
#define SHT_MINV (1.0f / SHT_MAX)

float fabsf(float f);
#pragma intrinsic(fabsf)
#ifdef __GNUC__
#define fabsf(f) __builtin_fabsf((float)(f))
#endif

double sqrt(double d);
#pragma intrinsic(sqrt)

float fmodf(float dividend, float divisor);

#endif

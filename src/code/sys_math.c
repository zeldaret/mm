/**
 * Maths library: two factorials, integer power, wrappers for libultra's sins and coss (the main ones used), and some
 * random functions moved from OoT's z_actor
 */
#include "global.h"

static f32 sFactorialTbl[] = { 1.0f,    1.0f,     2.0f,      6.0f,       24.0f,       120.0f,      720.0f,
                               5040.0f, 40320.0f, 362880.0f, 3628800.0f, 39916800.0f, 479001600.0f };

// Rename to Math_FactorialF
/**
 * Takes a float, returns the factorial of it(s trunctation), iteratively
 * Unused
 */
f32 func_80179300(f32 n) {
    f32 ret = 1.0f;
    s32 i;

    //! @bug No check for negative argument. Will return 1.0f if the argument truncates to a negative int.
    for (i = n; i > 1; i--) {
        ret *= i;
    }
    return ret;
}

// Rename to Math_Factorial
/**
 * Takes an int and returns its factorial as a float. Uses the lookup table for n <= 12.
 * Unused
 */
f32 func_80179400(s32 n) {
    f32 ret;
    s32 i;

    //! @bug No check for negative argument. Will read the array out-of-bounds if the argument is negative.
    //! (The OoT version does an unsigned check instead, which will return sFactorialTbl[12] for a negative argument.)
    if (n >= ARRAY_COUNT(sFactorialTbl)) {
        ret = sFactorialTbl[12];
        for (i = 13; i <= n; i++) {
            ret *= i;
        }
    } else {
        ret = sFactorialTbl[n];
    }
    return ret;
}

// Rename to Math_PowF
/**
 * Returns base^{exp} if exp is nonnegative and 1.0f otherwise.
 * Unused
 */
f32 pow_int(f32 base, s32 exp) {
    f32 ret = 1.0f;

    while (exp > 0) {
        exp--;
        ret *= base;
    }

    return ret;
}

// Rename to Math_SinF
/**
 * Takes an angle in radians and returns the sine.
 */
f32 sin_rad(f32 rad) {
    return sins(RADF_TO_BINANG(rad)) * SHT_MINV;
}

// Rename to Math_CosF
/**
 * Takes an angle in radians and returns the cosine.
 */
f32 cos_rad(f32 rad) {
    return coss(RADF_TO_BINANG(rad)) * SHT_MINV;
}

/**
 * Returns a pseudo-random floating-point number between 0.0f and scale. Originally in z_actor in OoT.
 */
f32 Rand_ZeroFloat(f32 scale) {
    return Rand_ZeroOne() * scale;
}

// Rename to Rand_CenteredFloat
/**
 * Returns a pseudo-random floating-point number between (- scale / 2) and (scale / 2). Originally in z_actor in OoT.
 */
f32 randPlusMinusPoint5Scaled(f32 scale) {
    return Rand_Centered() * scale;
}

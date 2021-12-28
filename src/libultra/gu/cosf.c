#include "libc/math.h"
#include "macros.h"

// A slightly tweaked form of the coefficients of the Maclaurin series of sine up to x^9
// [https://mathworld.wolfram.com/MaclaurinSeries.html].
// The commented versions do not match.
static const du P[] = {
    { 1.0 },                     // 1
    { -0.16666659550427756 },    // -1/3! = 1/6
    { 0.008333066246082155 },    // 1/5! = 1/120
    { -0.0001980960290193795 },  // -1/7! = -1/5040
    { 0.000002605780637968037 }, // 1/9! = 1/362880
};

static const du rpi = { 1 / 3.14159265358979323846 }; // 1/M_PI, "reciprocal of pi"

static const du pihi = { 3.1415926218032837 };

static const du pilo = { 3.178650954705639E-8 }; // pihi + pilo is the closest double to pi

static const fu zero = { 0x00000000 };

/**
 * Computes the cosine of a float, returning a float. It essentially computes sin(x+pi/2) by the same method as __sinf,
 * without as many size checks.
 */
f32 __cosf(f32 x) {
    f32 absx;
    f64 dx;         // x promoted to double
    f64 xSq;        // square of dx
    f64 polyApprox; // Most of Maclaurin polynomial of sin(x) of degree 9
    f64 dn;         // n promoted to double
    s32 n;          // number of multiples of pi away from the first half-period
    f64 result;
    s32 ix = *(s32*)&x;   // Type-pun x into an s32, i.e. its IEEE-754 hex representation
    s32 xpt = (ix >> 22); // Obtain the exponent of x (actually 2 * exponent + 127)

    xpt &= 0x1FF; // Remove the sign bit

    // |x| < 2^{28} (beyond this range, floats are too sparse to make the trig functions useable)
    if (xpt < 310) {
        absx = (x > 0) ? x : -x;
        dx = absx;

        dn = dx * rpi.d + 0.5;
        n = ROUND(dn);
        dn = n;

        dn -= 0.5;

        dx -= dn * pihi.d;
        dx -= dn * pilo.d;

        xSq = SQ(dx);
        polyApprox = ((P[4].d * xSq + P[3].d) * xSq + P[2].d) * xSq + P[1].d;
        result = dx + (dx * xSq) * polyApprox; // Actual Maclaurin polynomial for sin(x)

        if (n % 2 == 0) {
            return (f32)result;
        }
        return -(f32)result;
    }

    // if x is NaN
    if (x != x) {
        return __libm_qnan_f;
    }

    return zero.f;
}

#include "global.h"

// FCurve_CubicHermiteSpline
/**
 * Hermite cubic spline interpolation between two endpoints, a,b. More information available at
 * https://en.wikipedia.org/wiki/Cubic_Hermite_spline
 *
 * @param t interpolation parameter rescaled to lie in [0,1], (x-a)/(b-a)
 * @param interval distance (b-a) between the endpoints
 * @param y0 p(a)
 * @param y1 p(b)
 * @param m0 p'(a)
 * @param m1 p'(b)
 * @return f32 p(t), value of the cubic interpolating polynomial
 */
f32 func_800F23E0(f32 t, f32 interval, f32 y0, f32 y1, f32 m0, f32 m1) {
    f32 sq = t * t;
    f32 cube = sq * t;
    f32 temp_f18 = 2.0f * cube;
    f32 sp4 = sq * 3.0f;

    // Hermite basis cubics h_{ij} satisfy h_{ij}^{(j)}(i) = 1, the other three values being 0
    f32 h00 = temp_f18 - sp4 + 1.0f; // h_{00}(0) = 1
    f32 h01 = sp4 - temp_f18;        // h_{01}'(0) = 1
    f32 h10 = cube - 2.0f * sq + t;  // h_{10}(1) = 1
    f32 h11 = cube - sq;             // h_{11}'(1) = 1

    f32 ret = h00 * y0;

    ret += h01 * y1;
    ret += h10 * m0 * interval;
    ret += h11 * m1 * interval;

    return ret;
}

#define FCURVE_INTERP_CUBIC  0 // Interpolate using a Hermite cubic spline
#define FCURVE_INTERP_NONE   1 // Return the value at the left endpoint instead of interpolating
#define FCURVE_INTERP_LINEAR 2 // Interpolate linearly

// FCurve_Interpolate
/**
 * Interpolates based on an array of TransformData.
 *
 * @param x point at which to interpolate.
 * @param transData TransformData to use. Must have at least maxIndex elements
 * @param maxIndex 
 * @return f32 interpolated value
 */
f32 func_800F2478(f32 x, TransformData* transData, s32 maxIndex) {
    // If outside the entire interpolation interval, return the value at the near endpoint.
    if (x <= transData[0].abscissa) {
        return transData[0].ordinate;
    } else if (x >= transData[maxIndex - 1].abscissa) {
        return transData[maxIndex - 1].ordinate;
    } else {
        s32 cur;

        for (cur = 0;; cur++) {
            s32 next = cur + 1;
            // Find the subinterval in which x lies
            if (x < transData[next].abscissa) {
                if (transData[cur].flags & FCURVE_INTERP_NONE) {
                    // No interpolation
                    return transData[cur].ordinate;
                } else if (transData[cur].flags & FCURVE_INTERP_LINEAR) {
                    // Linear interpolation
                    return transData[cur].ordinate +
                        ((x - (f32)transData[cur].abscissa) / ((f32)transData[next].abscissa - (f32)transData[cur].abscissa)) *
                            (transData[next].ordinate - transData[cur].ordinate);
                } else {
                    // Cubic interpolation
                    f32 diff = (f32)transData[next].abscissa - (f32)transData[cur].abscissa;
                    return func_800F23E0((x - (f32)transData[cur].abscissa) / ((f32)transData[next].abscissa - (f32)transData[cur].abscissa),
                                        diff * (1.0f / 30.0f), transData[cur].ordinate, transData[next].ordinate,
                                        transData[cur].rightGradient, transData[next].leftGradient);
                }
            }
        }
    }
}

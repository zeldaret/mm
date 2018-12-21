#include <guint.h>

// TODO find these values wherever they are in .rodata
// TODO these can't be defined in here yet because we strip out the .rodata for each object
//static const du P[5];

//static const du rpi;

//static const du pihi;

//static const du pilo;

//static const fu zero;

extern du P[5];

extern du rpi;

extern du pihi;

extern du pilo;

extern fu zero;

extern float __libm_qnan_f;

float __sinf(float x) {
    double dx; // double x
    double xsq; // x squared
    double poly;
    double dn;
    int n;
    double result;
    int ix; // int x
    int xpt;

    ix = *(int*)&x;
    xpt = (ix >> 22) & 0x1FF;

    if (xpt < 255) {
        dx = x;
        if (xpt >= 230) {
            xsq = dx * dx;

            poly = (((((P[4].d * xsq) + P[3].d) * xsq) + P[2].d) * xsq) + P[1].d;

            result = ((dx * xsq) * poly) + dx;

            return result;
        } else {
            return x;
        }
    }

    if (xpt < 310) {
        dx = x;

        dn = dx * rpi.d;

        if (dn >= 0) {
            n = dn + 0.5;
        } else {
            n = dn - 0.5;
        }

        dn = n;

        dx -= dn * pihi.d;
        dx -= dn * pilo.d;

        xsq = dx * dx;

        poly = (((((P[4].d * xsq) + P[3].d) * xsq) + P[2].d) * xsq) + P[1].d;

        result = ((dx * xsq) * poly) + dx;

        if ((n & 0x1) == 0) {
            return result;
        } else {
            return -(float)result;
        }
    }

    if (x != x) {
        return __libm_qnan_f;
    }

    return zero.f;
}

#include <math.h>

static const du P[] = {
    { 0x3FF00000, 0x00000000 }, { 0xBFC55554, 0xBC83656D }, { 0x3F8110ED, 0x3804C2A0 },
    { 0xBF29F6FF, 0xEEA56814 }, { 0x3EC5DBDF, 0x0E314BFE },
};

static const du rpi = { 0x3FD45F30, 0x6DC9C883 };

static const du pihi = { 0x400921FB, 0x50000000 };

static const du pilo = { 0x3E6110B4, 0x611A6263 };

static const fu zero = { 0x00000000 };

extern float __libm_qnan_f;

float __sinf(float x) {
    double dx;  // double x
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

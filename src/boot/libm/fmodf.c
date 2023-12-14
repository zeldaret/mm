#include "libc/math.h"

float fmodf(float dividend, float divisor) {
    int quotient;

    if (divisor == 0.0f) {
        return 0.0f;
    }
    quotient = dividend / divisor;

    return dividend - quotient * divisor;
}

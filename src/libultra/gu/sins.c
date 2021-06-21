#include <math.h>

#include "sintable.h"

short sins(unsigned short x) {
    short val;

    x >>= 4;
    if ((x & 0x400) != 0) {
        val = sintable[0x3FF - (x & 0x3FF)];
    } else {
        val = sintable[x & 0x3FF];
    }

    if ((x & 0x800) != 0) {
        return -val;
    }

    return val;
}

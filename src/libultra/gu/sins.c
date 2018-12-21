#include <guint.h>
// TODO we can't include this because then sintable is placed in .data, which we strip out
//#include "sintable.h"
extern short sintable[1024];

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

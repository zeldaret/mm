#include "ultra64.h"
#include "global.h"

__OSViContext* __osViGetCurrentContext(void) {
    return __osViCurr;
}

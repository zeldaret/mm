#include <osint.h>
#include <viint.h>
#include <assert.h>

__OSViContext* __osViGetCurrentContext(void) {
    return __osViCurr;
}

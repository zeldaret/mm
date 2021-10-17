#include <ultra64.h>
#include <global.h>

void osSpTaskYield(void) {
    __osSpSetStatus(0x400);
}

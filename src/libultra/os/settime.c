#include <ultra64.h>
#include <global.h>

void osSetTime(OSTime ticks) {
    __osCurrentTime = ticks;
}

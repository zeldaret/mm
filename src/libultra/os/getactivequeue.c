#include <ultra64.h>
#include <global.h>

OSThread* __osGetActiveQueue(void) {
    return __osActiveQueue;
}

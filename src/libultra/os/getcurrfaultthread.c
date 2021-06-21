#include <ultra64.h>
#include <global.h>

OSThread* __osGetCurrFaultedThread(void) {
    return __osFaultedThread;
}

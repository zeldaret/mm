#include <ultra64.h>
#include <global.h>

OSPri osGetThreadPri(OSThread* t) {
    if (t == NULL) {
        t = __osRunningThread;
    }
    return t->priority;
}

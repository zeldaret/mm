#include "ultra64.h"
#include "global.h"

OSId osGetThreadId(OSThread* t) {
    if (t == NULL) {
        t = __osRunningThread;
    }
    return t->id;
}

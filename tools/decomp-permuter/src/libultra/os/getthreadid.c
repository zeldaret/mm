#include <osint.h>

OSId osGetThreadId(OSThread* t) {
    if (t == NULL) {
        t = __osRunningThread;
    }
    return t->id;
}

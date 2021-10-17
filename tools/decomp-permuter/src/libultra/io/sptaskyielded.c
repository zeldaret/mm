#include <ultra64.h>
#include <global.h>

OSYieldResult osSpTaskYielded(OSTask* task) {
    s32 status;
    OSYieldResult result;
    status = __osSpGetStatus();
    if (status & 0x100) {
        result = 1;
    } else {
        result = 0;
    }
    if (status & 0x80) {
        task->t.flags |= result;
        task->t.flags &= ~(2);
    }
    return result;
}

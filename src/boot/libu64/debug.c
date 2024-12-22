#include "global.h"
#include "fault.h"

NORETURN void _dbg_hungup(const char* file, int lineNum) {
    osGetThreadId(NULL);
    Fault_AddHungupAndCrash(file, lineNum);
}

NORETURN void Reset(void) {
    Fault_AddHungupAndCrash("Reset", 0);
}

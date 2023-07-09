#include "global.h"
#include "fault.h"

void __assert(const char* file, u32 lineNum) {
    osGetThreadId(NULL);
    Fault_AddHungupAndCrash(file, lineNum);
}

void func_800862B4(void) {
    Fault_AddHungupAndCrash("Reset", 0);
}

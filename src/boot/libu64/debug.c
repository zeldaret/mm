#include "global.h"
#include "fault.h"

#if MM_VERSION < N64_US || DEBUG_FEATURES
#define DEBUG_PRINTF osSyncPrintf
#elif IDO_PRINTF_WORKAROUND
#define DEBUG_PRINTF(args) (void)0
#else
#define DEBUG_PRINTF(format, ...) (void)0
#endif

#if MM_VERSION < N64_US
f32 LogUtils_CheckFloatRange(const char* exp, int line, const char* valueName, f32 value, const char* minName, f32 min,
                             const char* maxName, f32 max) {
    if (value < min || max < value) {
        osSyncPrintf("%s %d: range error %s(%f) < %s(%f) < %s(%f)\n", exp, line, minName, min, valueName, value,
                     maxName, max);
    }
    return value;
}
#endif

NORETURN void _dbg_hungup(const char* file, int lineNum) {
    OSId threadId = osGetThreadId(NULL);

    DEBUG_PRINTF("*** HungUp in thread %d, [%s:%d] ***\n", threadId, file, lineNum);
    Fault_AddHungupAndCrash(file, lineNum);
}

NORETURN void Reset(void) {
    DEBUG_PRINTF("*** Reset ***\n");
    Fault_AddHungupAndCrash("Reset", 0);
}

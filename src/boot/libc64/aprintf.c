#include "libc64/aprintf.h"

s32 vaprintf(PrintCallback* pfn, const char* fmt, va_list args) {
    return _Printf(*pfn, pfn, fmt, args);
}

s32 aprintf(PrintCallback* pfn, const char* fmt, ...) {
    s32 ret;
    va_list args;
    va_start(args, fmt);

    ret = vaprintf(pfn, fmt, args);

    va_end(args);

    return ret;
}

#include "libc64/aprintf.h"

int vaprintf(PrintCallback* pfn, const char* fmt, va_list args) {
    return _Printf(*pfn, pfn, fmt, args);
}

int aprintf(PrintCallback* pfn, const char* fmt, ...) {
    int ret;
    va_list args;
    va_start(args, fmt);

    ret = vaprintf(pfn, fmt, args);

    va_end(args);

    return ret;
}

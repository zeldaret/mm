#ifndef LIBC64_APRINTF_H
#define LIBC64_APRINTF_H

#include "ultra64.h"

s32 vaprintf(PrintCallback* pfn, const char* fmt, va_list args);
s32 aprintf(PrintCallback* pfn, const char* fmt, ...);

#endif

#ifndef LIBC64_SPRINTF_H
#define LIBC64_SPRINTF_H

#include "ultra64.h"

int vsprintf(char* dst, const char* fmt, va_list args);
int sprintf(char* dst, const char* fmt, ...);

#endif

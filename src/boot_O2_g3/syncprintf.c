#include "global.h"

// This isn't a vprintf since it doesn't take a va_list
void __osSyncVPrintf(const char* fmt, ...) {
}

void osSyncPrintf(const char* fmt, ...) {
}

void rmonPrintf(const char* fmt, ...) {
}

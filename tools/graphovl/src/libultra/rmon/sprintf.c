#include "global.h"

void* proutSprintf(void* dst, const char* fmt, size_t size) {
    return (void*)((uintptr_t)memcpy(dst, fmt, size) + size);
}

int vsprintf(char* dst, char* fmt, va_list args) {
    int ans = _Printf(proutSprintf, dst, fmt, args);
    if (ans > -1) {
        dst[ans] = 0;
    }
    return ans;
}

int sprintf(char* dst, char* fmt, ...) {
    int ans;
    va_list args;
    va_start(args, fmt);

    ans = _Printf(&proutSprintf, dst, fmt, args);
    if (ans > -1) {
        dst[ans] = 0;
    }

    va_end(args);

    return ans;
}

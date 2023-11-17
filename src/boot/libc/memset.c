#include "libc/string.h"

void* memset(void* ptr, int val, size_t size) {
    unsigned char* dst = ptr;
    register size_t rem;

    for (rem = size--; rem != 0; rem = size--) {
        *dst++ = val;
    }

    return ptr;
}

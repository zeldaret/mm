#include "libc/string.h"

void* memmove(void* dst, const void* src, size_t size) {
    unsigned char* _dst = dst;
    const unsigned char* _src = src;
    register size_t rem;

    if (_dst == _src) {
        return dst;
    }
    if (_dst < _src) {
        for (rem = size--; rem != 0; rem = size--) {
            *_dst++ = *_src++;
        }
    } else {
        _dst += size - 1;
        _src += size - 1;
        for (rem = size--; rem != 0; rem = size--) {
            *_dst-- = *_src--;
        }
    }
    return dst;
}

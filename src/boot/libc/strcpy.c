#include "libc/string.h"

char* strcpy(char* dst, const char* src) {
    char* _dst = dst;

    while (*src != '\0') {
        *_dst++ = *src++;
    }
    *_dst = '\0';

    return dst;
}

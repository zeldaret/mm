#include <string.h>

unsigned char* strchr(const unsigned char* s, int c) {
    const unsigned char ch = c;

    while (*s != ch) {
        if (*s == '\0') {
            return NULL;
        }
        s++;
    }

    return (unsigned char*)s;
}

size_t strlen(const unsigned char* s) {
    const unsigned char* sc = s;

    while (*sc != '\0') {
        sc++;
    }

    return (size_t)(sc - s);
}

void* memcpy(void* s1, const void* s2, size_t n) {
    unsigned char* su1 = (unsigned char*)s1;
    const unsigned char* su2 = (const unsigned char*)s2;

    while (n > 0) {
        *su1 = *su2;
        su1++;
        su2++;
        n--;
    }

    return s1;
}

#include <ultra64.h>
#include <global.h>

/*
 * Compare strings (strcmp).
 */
s32 func_800968B0(const char* str1, const char* str2) {
    char v0;
    char v1;
    do {
        v0 = *str1++;
        v1 = *str2++;
        if (v0 != v1) {
          return v0 - v1;
        }
    } while (v0);
    return 0;
}

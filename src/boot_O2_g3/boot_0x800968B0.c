#include <ultra64.h>
#include <global.h>

/*
 * Compare strings (strcmp).
 */
s32 func_800968B0(const char* str1, const char* str2) {
    char currentCharStr1;
    char currentCharStr2;
    do {
        currentCharStr1 = *str1++;
        currentCharStr2 = *str2++;
        if (currentCharStr1 != currentCharStr2) {
            return currentCharStr1 - currentCharStr2;
        }
    } while (currentCharStr1);

    return 0;
}

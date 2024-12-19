#include "libc64/sleep.h"
#include "attributes.h"

NORETURN void func_80183070(void) {
    for (;;) {
        msleep(1000);
    }
}

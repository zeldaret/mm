#include "libc64/sleep.h"
#include "attributes.h"

NORETURN void Sys_Freeze(void) {
    for (;;) {
        msleep(1000);
    }
}

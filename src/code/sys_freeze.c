#include "libc64/sleep.h"
#include "attributes.h"

#include "macros.h"

NORETURN void Sys_Freeze(void) {
    PRINTF("\n**** Freeze!! ****\n");
    for (;;) {
        msleep(1000);
    }
}

#include "libc64/sleep.h"

void Sleep_Forever(void) {
    for (;;) {
        msleep(1000);
    }
}
